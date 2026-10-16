#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "AudioPlayer.h"
#include "PlaylistManager.h"
#include <string>

class ConsoleUI {
public:
    void run();

private:
    PlaylistManager manager_;
    AudioPlayer player_;

    std::string ask(const std::string& prompt) const;
    int number(const std::string& prompt, int min, int max) const;
    int selectPlaylist() const;
    void showSurahs(const Playlist& playlist) const;
    void addPlaylist();
    void addSurah();
    void removeSurah();
    void reorderSurah();
    void showAllPlaylists() const;
    void showPlaylistNames() const;
    void showOnePlaylist() const;
    void playPlaylist() const;
    void savePlaylists() const;
    void loadPlaylists();
    void removePlaylist();
};

#endif
