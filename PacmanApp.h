#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"

class PacmanApp
{
public:
	PacmanApp();
	~PacmanApp();
	sf::RenderWindow window;
	Scene* currentScene;
	void Run();
	void Update();
private:
	sf::View view;
	int windowWidth;
	int windowHeight;
	void Draw();
	sf::Clock frameClock;
	sf::Event event;
};

