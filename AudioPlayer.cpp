#include "AudioPlayer.h"

#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#ifdef _MSC_VER
#pragma comment(lib, "winmm.lib")
#endif

namespace {
std::string mciErrorMessage(MCIERROR error) {
    char message[256] = {};
    if (mciGetErrorStringA(error, message, sizeof(message))) return message;
    return "Unknown Windows Multimedia error (code " + std::to_string(error) + ")";
}
}
#endif

using namespace std;

void AudioPlayer::play(const Playlist& playlist) const {
#ifndef _WIN32
    (void)playlist;
    cout << "Audio playback in this version requires Windows.\n";
#else
    const SinglyLinkedList<Surah>& surahs = playlist.getSurahs();
    if (surahs.empty()) {
        cout << "Playlist is empty.\n";
        return;
    }

    size_t current = 0;
    while (current < surahs.size()) {
        const Surah& surah = *surahs.at(current);
        const DWORD attributes = GetFileAttributesA(surah.getFile().c_str());
        if (attributes == INVALID_FILE_ATTRIBUTES || (attributes & FILE_ATTRIBUTE_DIRECTORY)) {
            cout << "Audio file does not exist or is not a file: " << surah.getFile() << '\n'
                 << "Use the full path to an MP3 file, for example C:\\Quran\\Al-Baqarah.mp3.\n";
            ++current;
            continue;
        }

        const string command = "open \"" + surah.getFile() + "\" type mpegvideo alias quran";
        mciSendStringA("close quran", nullptr, 0, nullptr);
        MCIERROR error = mciSendStringA(command.c_str(), nullptr, 0, nullptr);
        if (error != 0) {
            cout << "Windows could not open audio file: " << surah.getFile() << '\n'
                 << "Reason: " << mciErrorMessage(error) << '\n';
            ++current;
            continue;
        }
        error = mciSendStringA("play quran", nullptr, 0, nullptr);
        if (error != 0) {
            cout << "Windows opened the file but could not play it: " << surah.getFile() << '\n'
                 << "Reason: " << mciErrorMessage(error) << '\n';
            mciSendStringA("close quran", nullptr, 0, nullptr);
            ++current;
            continue;
        }

        cout << "Playing " << surah.getName()
             << " | Left: previous | Right: next | Up: pause | Down: resume | Q: stop\n";
        bool paused = false;
        bool changedTrack = false;
        while (!changedTrack) {
            if (_kbhit()) {
                const int key = _getch();
                if (key == 'q' || key == 'Q') {
                    mciSendStringA("close quran", nullptr, 0, nullptr);
                    return;
                }
                if (key == 0 || key == 224) {
                    const int arrow = _getch();
                    if (arrow == 75) {
                        current = current == 0 ? surahs.size() - 1 : current - 1;
                        changedTrack = true;
                    } else if (arrow == 77) {
                        ++current;
                        if (current == surahs.size()) current = 0;
                        changedTrack = true;
                    } else if (arrow == 72 && !paused) {
                        mciSendStringA("pause quran", nullptr, 0, nullptr);
                        paused = true;
                    } else if (arrow == 80 && paused) {
                        mciSendStringA("resume quran", nullptr, 0, nullptr);
                        paused = false;
                    }
                }
            }
            char mode[32] = {};
            mciSendStringA("status quran mode", mode, sizeof(mode), nullptr);
            if (string(mode) == "stopped") {
                ++current;
                changedTrack = true;
            }
            Sleep(100);
        }
        mciSendStringA("close quran", nullptr, 0, nullptr);
    }
#endif
}
