//
// Created by ndv on 6/1/19.
//

#include "AudioSystem.h"

AudioSystem::AudioSystem() {
    //TODO: Cargar musica y efectos de sonido desde un yaml.
    this->backgroundMusic = Mix_LoadMUS("resources/sounds/outrun_the_reaper.mp3");
    Mix_VolumeMusic(MUSIC_VOLUME);
}

AudioSystem::~AudioSystem() {
    Mix_FreeMusic(this->backgroundMusic);
}

void AudioSystem::playMusic() {
    if (Mix_PlayingMusic() == 0){
        // We set the second parameter to -1 to loop the track.
        Mix_PlayMusic(backgroundMusic, -1);
    }
}

void AudioSystem::stopMusic() {
    if (Mix_PlayingMusic()){
        Mix_HaltMusic();
    }
}
