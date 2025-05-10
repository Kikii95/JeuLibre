#include "pch.h"

ComponentAudio::ComponentAudio(Entity* entity) : Component(entity) {}

void ComponentAudio::AddSound(SoundType type, const std::string& file) {
    soundFiles[type] = file;
}

bool ComponentAudio::LoadSound(SoundType type) {
    if (soundFiles.find(type) == soundFiles.end()) {
        std::cerr << "[ERROR] Aucun fichier audio trouve pour ce type." << std::endl;
        return false;
    }

    std::string filePath = soundFiles[type];

    if (!soundBuffers[type].loadFromFile(filePath)) {
        std::cerr << "[ERROR] Impossible de charger le son : " << filePath << std::endl;
        return false;
    }
    sounds.emplace(type, soundBuffers[type]);
    //sounds[type].setBuffer(soundBuffers[type]);
    sounds.at(type).setVolume(volume);
    return true;
}

void ComponentAudio::PlaySound(SoundType type) {
    if (sounds.find(type) == sounds.end()) {
        if (!LoadSound(type)) {
            return; 
        }
    }

    sounds.at(type).play();
}

void ComponentAudio::StopSound(SoundType type) {
    if (sounds.find(type) != sounds.end()) {
        sounds.at(type).stop();
    }
}

void ComponentAudio::SetVolume(float newVolume) {
    volume = newVolume;
    for (auto& pair : sounds) {
        pair.second.setVolume(volume);
    }
}

float ComponentAudio::GetVolume() const {
    return volume;
}
