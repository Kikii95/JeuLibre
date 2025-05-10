#pragma once

class ToolBoxAssets : public ToolBox {
public:
    static ToolBoxAssets& GetInstance();

    bool LoadImageFromFile(const std::string& filePath, sf::Image& image);
    bool LoadFontFromFile(const std::string& path, const std::string& name);
    bool LoadTextureFromFile(const std::string& filePath, sf::Texture& texture);
    sf::SoundBuffer* LoadSoundFromFile(const std::string& filePath);
    sf::Font* GetFont(const std::string& name);
    sf::Vector2f MeasureTextSize(const std::string& text, const std::string& fontName, unsigned int charSize);
	void PreloadFonts();

private:
    std::map<std::string, sf::SoundBuffer> soundBufferCache;
    std::map<std::string, sf::Font> fontCache;

    //ToolBoxAssets() = default;
    //ToolBoxAssets(const ToolBoxAssets&) = delete;
    //ToolBoxAssets& operator=(const ToolBoxAssets&) = delete;
};
