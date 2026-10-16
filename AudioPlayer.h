#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "Playlist.h"

class AudioPlayer {
public:
    void play(const Playlist& playlist) const;
};

#endif
