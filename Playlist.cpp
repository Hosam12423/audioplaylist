#include "Playlist.h"

using namespace std;

Playlist::Playlist(const string& name) : name_(name) {}

const string& Playlist::getName() const { return name_; }
const SinglyLinkedList<Surah>& Playlist::getSurahs() const { return surahs_; }
bool Playlist::isEmpty() const { return surahs_.empty(); }

void Playlist::addSurah(const Surah& surah) { surahs_.push_back(surah); }

bool Playlist::removeSurah(size_t index) {
    return surahs_.removeAt(index);
}

bool Playlist::moveSurah(size_t from, size_t to) {
    return surahs_.move(from, to);
}
