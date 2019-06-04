//
// Created by ndv on 6/1/19.
//

#ifndef PORTAL_AUDIOSYSTEM_H
#define PORTAL_AUDIOSYSTEM_H

#include <SDL_mixer.h>
#include <unordered_map>
#include "SoundCodeQueue.h"
#include "../common/constants.h"

#define MUSIC_VOLUME 50
#define JUMP_VOLUME 30

class AudioSystem {
    Mix_Music* backgroundMusic;
    std::unordered_map<int, Mix_Chunk*> soundEffects;
    SoundCodeQueue& soundsQueue;
public:
    AudioSystem(SoundCodeQueue& queue);
    ~AudioSystem();
    void playMusic();
    void stopMusic();
    void playSoundEffects();
};


#endif //PORTAL_AUDIOSYSTEM_H
