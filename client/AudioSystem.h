//
// Created by ndv on 6/1/19.
//

#ifndef PORTAL_AUDIOSYSTEM_H
#define PORTAL_AUDIOSYSTEM_H

#include <SDL_mixer.h>
#include <unordered_map>
#include <queue>

#define MUSIC_VOLUME 50
#define JUMP_SOUND 3
#define RUN_SOUND 0

class AudioSystem {
    Mix_Music* backgroundMusic;
    std::unordered_map<int, Mix_Chunk*> soundEffects;
    std::queue<int> soundsQueue;
public:
    AudioSystem();
    ~AudioSystem();
    void playMusic();
    void stopMusic();
    void queueSound(int soundCode);
    void playSoundEffects();
};


#endif //PORTAL_AUDIOSYSTEM_H
