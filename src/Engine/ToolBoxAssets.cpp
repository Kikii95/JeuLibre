#include "pch.h"

ToolBoxAssets& ToolBoxAssets::GetInstance() {
    static ToolBoxAssets instance;
    return instance;
}


bool ToolBoxAssets::LoadImageFromFile(const std::string& filePath, sf::Image& image) {
    if (!image.loadFromFile(filePath)) {
        std::cerr << "[ERROR] Impossible de charger l'image : " << filePath << std::endl;
        return false;
    }
    return true;
}

bool ToolBoxAssets::LoadFontFromFile(const std::string& path, const std::string& name) {
    sf::Font font;
    if (!font.openFromFile(path)) {
        std::cerr << "[ERROR] Échec du chargement de la police : " << path << "\n";
        return false;
    }
    fontCache[name] = std::move(font);
    return true;
}

bool ToolBoxAssets::LoadTextureFromFile(const std::string& filePath, sf::Texture& texture) {
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "[ERROR] Impossible de charger la texture : " << filePath << std::endl;
        return false;
    }
    return true;
}

sf::SoundBuffer* ToolBoxAssets::LoadSoundFromFile(const std::string& filePath) {
    auto it = soundBufferCache.find(filePath);
    if (it != soundBufferCache.end()) {
        return &it->second;
    }

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath)) {
        std::cerr << "[ERROR] Impossible de charger le son : " << filePath << std::endl;
        return nullptr;
    }

    soundBufferCache[filePath] = std::move(buffer);
    return &soundBufferCache[filePath];
}

sf::Font* ToolBoxAssets::GetFont(const std::string& name) {
    auto it = fontCache.find(name);
    if (it != fontCache.end()) {
        return &it->second;
    }
    std::cerr << "[WARN] Police non trouvée : " << name << "\n";
    return nullptr;
}

sf::Vector2f ToolBoxAssets::MeasureTextSize(const std::string& text, const std::string& fontName, unsigned int charSize) {
    sf::Font* font = GetFont(fontName);
    if (!font) {
        std::cerr << "[ERROR] MeasureTextSize : police '" << fontName << "' introuvable.\n";
        return { 0.f, 0.f };
    }

    sf::Text measure(*font, text);
    measure.setCharacterSize(charSize);

    sf::FloatRect bounds = measure.getLocalBounds();
    sf::Vector2f size(bounds.size);

    return size;
}

void ToolBoxAssets::PreloadFonts() {
    sf::Font* font = GetFont("testFont");
    if (!font) return;

    sf::Text dummy(*font); 

    for (int size = 8; size <= 50; ++size) {
        dummy.setCharacterSize(size);
        dummy.setString("Préchargement");
        sf::FloatRect bounds = dummy.getLocalBounds(); 
    }

    std::cout << "[Font] Préchargement des tailles terminé." << std::endl;
}
