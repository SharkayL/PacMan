#pragma once
#include "BackGround.h"

class PacmanApp;

class Scene
{
public:
	Scene(PacmanApp &app);
	~Scene();
	virtual void Update(sf::Time timeDelta);
	virtual void HandleEvent(sf::Event event);
	virtual void Draw(sf::RenderWindow &window);
	bool play;
	bool win;
	bool menu;
	bool displayScore;

private:
	BackGround bgd;
};

