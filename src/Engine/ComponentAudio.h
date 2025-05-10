#pragma once


enum class SoundType {
    SHOOT,
    FOOTSTEP,
    DAMAGE
};

class ComponentAudio : public Component {
private:
    std::map<SoundType, std::string> soundFiles;
    std::map<SoundType, sf::SoundBuffer> soundBuffers;
    std::map<SoundType, sf::Sound> sounds;

    float volume = 100.0f; 

public:
    ComponentAudio(Entity* entity);

    void AddSound(SoundType type, const std::string& file);
    bool LoadSound(SoundType type);

    void PlaySound(SoundType type);
    void StopSound(SoundType type);

    void SetVolume(float newVolume);
    float GetVolume() const;
};
