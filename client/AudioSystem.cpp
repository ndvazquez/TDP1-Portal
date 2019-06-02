//
// Created by ndv on 6/1/19.
//

#include "AudioSystem.h"

AudioSystem::AudioSystem(SoundCodeQueue& queue) : soundsQueue(queue) {
    //TODO: Cargar musica y efectos de sonido desde un yaml.
    this->backgroundMusic = Mix_LoadMUS("resources/sounds/outrun_the_reaper.mp3");
    Mix_VolumeMusic(MUSIC_VOLUME);
    Mix_Chunk* jumpEffect = Mix_LoadWAV("resources/sounds/jump.wav");
    Mix_VolumeChunk(jumpEffect, 50);
    Mix_Chunk* runEffect = Mix_LoadWAV("resources/sounds/step1.wav");
    soundEffects.insert({JUMP_SOUND, jumpEffect});
    soundEffects.insert({RUN_SOUND, runEffect});
}

AudioSystem::~AudioSystem() {
    Mix_FreeMusic(this->backgroundMusic);
    for (auto it = soundEffects.begin(); it != soundEffects.end(); ++it){
        Mix_FreeChunk(it->second);
    }
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

void AudioSystem::queueSound(int soundCode) {
    this->soundsQueue.push(soundCode);
}

void AudioSystem::playSoundEffects() {
    while (!this->soundsQueue.empty()){
        int soundCode = this->soundsQueue.front();
        this->soundsQueue.pop();
        auto it = this->soundEffects.find(soundCode);
        if (it != this->soundEffects.end()){
            Mix_Chunk* soundEffect = it->second;
            Mix_PlayChannel(-1, soundEffect, 0);
        }
    }
}
