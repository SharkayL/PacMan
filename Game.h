#pragma once
#include "Ghosts.h"
#include "Dots.h"
#include "Scene.h"
#include "Pacman.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Pokey.h"
#include "ChaseStates.h"
#include "Fruits.h"
#include "Score.h"

class Game : public Scene
{
public:
	Game(PacmanApp &app);
	~Game();
	void HandleEvent(sf::Event event) override;
	void Draw(sf::RenderWindow &window) override;
	virtual void Update(sf::Time timeDelta) override;
	int pmGrid[28][36];
	ChaseStates gameStates;
	bool Init();
	Pacman pacman;
	Blinky blinky;
	Pinky pinky;
	Inky inky;
	Pokey pokey;
	Dots dots;
	void Scatter();
	void Chase();
	int score;
	sf::Font font;
	sf::Text scoreText;
	void ScoreText();
	Fruits fruits;
	sf::Sprite cherry;
	Score finalScore;
private:
	sf::Vector2i dir;
	sf::Time elapseTime;
	sf::Time orderTimer;
	sf::Time drawingTimer;
	bool bonus;
	bool gotBonus;
};

