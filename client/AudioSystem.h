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
#define SOUNDS_RESOURCES_FILE "config/sounds.yaml"
#define SONGS_KEY "Music"
#define SONG_CODE_KEY "songCode"
#define SONG_PATH_KEY "path"
#define EFFECTS_KEY "SoundEffects"
#define EFFECT_CODE_KEY "soundCode"
#define EFFECT_VOLUME_KEY "volume"

class AudioSystem {
    std::unordered_map<int, Mix_Music*> backgroundMusic;
    std::unordered_map<int, Mix_Chunk*> soundEffects;
    SoundCodeQueue& soundsQueue;
public:
    explicit AudioSystem(SoundCodeQueue& queue);
    ~AudioSystem();
    void playMusic(int songCode);
    void stopMusic();
    void playSoundEffects();
};


#endif //PORTAL_AUDIOSYSTEM_H
