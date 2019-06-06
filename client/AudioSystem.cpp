//
// Created by ndv on 6/1/19.
//

#include "AudioSystem.h"
#include <yaml-cpp/yaml.h>

AudioSystem::AudioSystem(SoundCodeQueue& queue) : soundsQueue(queue) {
    //TODO: Manejo de excepciones.
    YAML::Node soundResources = YAML::LoadFile(SOUNDS_RESOURCES_FILE);
    YAML::Node songs = soundResources[SONGS_KEY];
    for (YAML::const_iterator it = songs.begin(); it != songs.end(); ++it){
        YAML::Node node = *it;
        int songCode = node[SONG_CODE_KEY].as<int>();
        std::string path = node[SONG_PATH_KEY].as<std::string>();
        Mix_Music* song = Mix_LoadMUS(path.c_str());
        backgroundMusic.insert({songCode, song});
    }
    YAML::Node effects = soundResources[EFFECTS_KEY];
    for (YAML::const_iterator it = effects.begin(); it != effects.end(); ++it){
        YAML::Node node = *it;
        int soundCode = node[EFFECT_CODE_KEY].as<int>();
        int soundVolume = node[EFFECT_VOLUME_KEY].as<int>();
        std::string path = node[SONG_PATH_KEY].as<std::string>();
        Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
        Mix_VolumeChunk(sound, soundVolume);
        soundEffects.insert({soundCode, sound});
    }
    Mix_VolumeMusic(MUSIC_VOLUME);
}

AudioSystem::~AudioSystem() {
    for (auto it = backgroundMusic.begin(); it != backgroundMusic.end(); ++it){
        Mix_FreeMusic(it->second);
    }
    for (auto it = soundEffects.begin(); it != soundEffects.end(); ++it){
        Mix_FreeChunk(it->second);
    }
}

void AudioSystem::playMusic(int songCode) {
    if (Mix_PlayingMusic() == 0) {
        // We set the second parameter to -1 to loop the track.
        auto it = this->backgroundMusic.find(songCode);
        if (it == this->backgroundMusic.end()) return;
        Mix_Music* song = it->second;
        Mix_PlayMusic(song, -1);
    }
}

void AudioSystem::stopMusic() {
    if (Mix_PlayingMusic()){
        Mix_HaltMusic();
    }
}

void AudioSystem::playSoundEffects() {
    while (!this->soundsQueue.empty()) {
        int soundCode = this->soundsQueue.front();
        this->soundsQueue.pop();
        auto it = this->soundEffects.find(soundCode);
        if (it != this->soundEffects.end()) {
            Mix_Chunk* soundEffect = it->second;
            Mix_PlayChannel(-1, soundEffect, 0);
        }
    }
}
