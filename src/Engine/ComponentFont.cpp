#include "pch.h"
#include "ComponentFont.h"

ComponentFont::ComponentFont(Entity* owner)
	: Component(owner), mText(mFont)
{
}

ComponentFont::~ComponentFont() {}

void ComponentFont::SetFontByName(const std::string& fontName) {
	sf::Font* font = ToolBoxAssets::GetInstance().GetFont(fontName);
	if (font) {
		mFont = *font;
		mText.setFont(mFont);
		this->fontName = fontName;
	}
}

std::string ComponentFont::GetFontName() const {
	return fontName;
}


void ComponentFont::SetText(const std::string& text, bool resize) {
	mText.setString(text);

	if (resize) {
		SetTextAutoFitToBox(text);
	}

}

sf::Text ComponentFont::GetText() {
	return mText; 
}

void ComponentFont::SetAutoFitText(bool value) {
	autoFitText = value;
}

bool ComponentFont::IsAutoFitText() const {
	return autoFitText;
}

const std::optional<std::string>& ComponentFont::GetDeferredText() const {
	return deferredText;
}

void ComponentFont::SetDeferredText(const std::string& txt) {
	deferredText = txt;
}

void ComponentFont::ClearDeferredText() {
	deferredText.reset();
}


void ComponentFont::SetCharacterSize(unsigned int size) {
	mText.setCharacterSize(size);
}

void ComponentFont::SetFillColor(const sf::Color& color) {
	mText.setFillColor(color);
}

void ComponentFont::SetPosition(const sf::Vector2f& pos) {
	mText.setPosition(pos);
}

sf::Vector2f ComponentFont::GetPosition() const {
	return mText.getPosition();
}

void ComponentFont::SetFixedOnScreen(bool value) {
	fixedOnScreen = value;
}

bool ComponentFont::IsFixedOnScreen() const {
	return fixedOnScreen;
}

void ComponentFont::SetIsOffsetManually(bool offset) {
	isOffsetManually = offset;
}

bool ComponentFont::IsOffsetManually() const {
	return isOffsetManually;
}

void ComponentFont::SetManualOffset(const sf::Vector2f& offset) {
	manualOffset = offset;
	isOffsetManually = true;
}

sf::Vector2f ComponentFont::GetManualOffset() const {
	return manualOffset;
}

void ComponentFont::SetTextAutoFitToBox(const std::string& text, float maxSizeRatio) {
	mText.setString(text);

	ComponentTransform* transform = GetEntity()->GetComponent<ComponentTransform>();
	if (!transform) return;

	sf::Vector2f boxSize = transform->GetSize();
	if (boxSize.x <= 0.f || boxSize.y <= 0.f) return;

	const unsigned int maxCharSize = 200;
	unsigned int charSize = maxCharSize;
	mText.setCharacterSize(charSize);

	sf::FloatRect bounds = mText.getLocalBounds();

	while ((bounds.size.x > boxSize.x * maxSizeRatio || bounds.size.y > boxSize.y * maxSizeRatio) && charSize > 4) {
		charSize -= 1;
		mText.setCharacterSize(charSize);
		bounds = mText.getLocalBounds();
	}

	mText.setCharacterSize(charSize);
}

void ComponentFont::SetAutoSizePadding(float padding) {
	autoSizePadding = padding;
}

void ComponentFont::SetBoxAutoFitText(const std::string& text) {
	ComponentTransform* transform = GetEntity()->GetComponent<ComponentTransform>();
	if (transform) {
		sf::FloatRect bounds = mText.getLocalBounds();
		sf::Vector2f size(bounds.size.x + 2 * autoSizePadding, bounds.size.y + 2 * autoSizePadding);
		transform->SetSize(size);
	}
}