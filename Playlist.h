#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Surah.h"
#include "SinglyLinkedList.h"
#include <cstddef>
#include <string>

class Playlist {
public:
    explicit Playlist(const std::string& name = std::string());

    const std::string& getName() const;
    const SinglyLinkedList<Surah>& getSurahs() const;
    bool isEmpty() const;
    void addSurah(const Surah& surah);
    bool removeSurah(std::size_t index);
    bool moveSurah(std::size_t from, std::size_t to);

private:
    std::string name_;
    SinglyLinkedList<Surah> surahs_;

    friend class PlaylistManager;
};

#endif
