#ifndef PLAYLIST_MANAGER_H
#define PLAYLIST_MANAGER_H

#include "Playlist.h"
#include "Stack.h"
#include <cstddef>
#include <string>

class PlaylistManager {
public:
    const Stack<Playlist>& getPlaylists() const;
    bool isEmpty() const;
    void addPlaylist(const std::string& name);
    bool removePlaylist(std::size_t index);
    Playlist* getPlaylist(std::size_t index);
    const Playlist* getPlaylist(std::size_t index) const;
    bool saveToFile(const std::string& path) const;
    bool loadFromFile(const std::string& path);

private:
    Stack<Playlist> playlists_;
};

#endif
