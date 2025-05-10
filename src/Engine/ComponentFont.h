#pragma once
#include "Component.h"

class ComponentFont :public Component
{
private:
	sf::Font mFont;
	sf::Text mText;
	std::string fontName;

	bool fixedOnScreen = false;
	float autoSizePadding = 10.0f;
	bool autoFitText = false;

	sf::Vector2f manualOffset = { 0.f, 0.f };
	bool isOffsetManually = false;


	std::optional<std::string> deferredText;

public:
	ComponentFont(Entity* owner);
	~ComponentFont();

	void SetFontByName(const std::string& fontName);
	std::string GetFontName() const;

	void SetText(const std::string& text, bool resize);
	sf::Text GetText();

	void SetAutoFitText(bool value);
	bool IsAutoFitText() const;

	const std::optional<std::string>& GetDeferredText() const;
	void SetDeferredText(const std::string& txt);
	void ClearDeferredText();

	void SetCharacterSize(unsigned int size);
	void SetFillColor(const sf::Color& color);

	void SetPosition(const sf::Vector2f& pos);
	sf::Vector2f GetPosition() const;

	void SetFixedOnScreen(bool value);
	bool IsFixedOnScreen() const;

	void SetIsOffsetManually(bool offset);
	bool IsOffsetManually() const;
	void SetManualOffset(const sf::Vector2f& offset);
	sf::Vector2f GetManualOffset() const;

	void SetTextAutoFitToBox(const std::string& text, float maxSizeRatio = 0.95f);
	void SetBoxAutoFitText(const std::string& text);
	void SetAutoSizePadding(float padding);

};