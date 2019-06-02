//
// Created by ndv on 6/1/19.
//

#ifndef PORTAL_AUDIOSYSTEM_H
#define PORTAL_AUDIOSYSTEM_H

#include <SDL_mixer.h>
#define MUSIC_VOLUME 25

class AudioSystem {
    Mix_Music* backgroundMusic;
public:
    AudioSystem();
    ~AudioSystem();
    void playMusic();
    void stopMusic();
};


#endif //PORTAL_AUDIOSYSTEM_H
