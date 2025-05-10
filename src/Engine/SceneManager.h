#pragma once
class SceneManager
{
private:
	sf::RenderWindow* mpWindow;
	int mWindowWidth;
	int mWindowHeight;

	sf::Color mClearColor;

public:
	SceneManager();
	~SceneManager();
	void CreateWindow(unsigned int width, unsigned int height, const char* title, int fpslimit, sf::Color clearColor);
	void Run();
	void Draw();
};

