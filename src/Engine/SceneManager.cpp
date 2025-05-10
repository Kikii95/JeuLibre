#include "pch.h"

SceneManager::SceneManager()
{
	mpWindow = nullptr;
	mWindowWidth = 0;
	mWindowHeight = 0;
}

SceneManager::~SceneManager()
{
	delete mpWindow;
}

void SceneManager::CreateWindow(unsigned int width, unsigned int height, const char* title, int fpslimit, sf::Color clearColor)
{
	mpWindow = new sf::RenderWindow(sf::VideoMode({width, height}), title);
	mpWindow->setFramerateLimit(fpslimit);

	mWindowWidth = width;
	mWindowHeight = height;
	mClearColor = clearColor;
}

void SceneManager::Run()
{
	while (mpWindow->isOpen())
	{
		while (const std::optional event = mpWindow->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				mpWindow->close();
			}
		}
		Draw();
		mpWindow->display();
	}
}

void SceneManager::Draw()
{
	mpWindow->clear(mClearColor);
}

