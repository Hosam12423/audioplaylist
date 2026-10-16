#include "PlaylistManager.h"

#include <cstddef>
#include <fstream>
#include <iomanip>

using namespace std;

const Stack<Playlist>& PlaylistManager::getPlaylists() const { return playlists_; }
bool PlaylistManager::isEmpty() const { return playlists_.empty(); }
void PlaylistManager::addPlaylist(const string& name) { playlists_.push(Playlist(name)); }

bool PlaylistManager::removePlaylist(size_t index) {
    return playlists_.removeAt(index);
}

Playlist* PlaylistManager::getPlaylist(size_t index) {
    return playlists_.at(index);
}

const Playlist* PlaylistManager::getPlaylist(size_t index) const {
    return playlists_.at(index);
}

bool PlaylistManager::saveToFile(const string& path) const {
    ofstream out(path);
    if (!out) return false;
    out << playlists_.size() << '\n';
    for (const Playlist& playlist : playlists_) {
        out << quoted(playlist.name_) << ' ' << playlist.surahs_.size() << '\n';
        for (const Surah& surah : playlist.surahs_)
            out << quoted(surah.getName()) << ' ' << quoted(surah.getType())
                << ' ' << quoted(surah.getFile()) << '\n';
    }
    return static_cast<bool>(out);
}

bool PlaylistManager::loadFromFile(const string& path) {
    ifstream in(path);
    if (!in) return false;

    int count;
    if (!(in >> count) || count < 0 || count > 10000) return false;
    Stack<Playlist> loaded;
    for (int i = 0; i < count; ++i) {
        string name;
        int surahCount;
        if (!(in >> quoted(name) >> surahCount) || surahCount < 0 || surahCount > 100000)
            return false;
        Playlist playlist(name);
        for (int j = 0; j < surahCount; ++j) {
            string surahName, type, file;
            if (!(in >> quoted(surahName) >> quoted(type) >> quoted(file)))
                return false;
            playlist.addSurah(Surah(surahName, type, file));
        }
        loaded.pushBottom(playlist);
    }
    playlists_.swap(loaded);
    return true;
}
