#pragma once
#include "Scene.h"
#include "Score.h"
class ScoreBoard : public Scene, public Score
{
public:
	ScoreBoard(PacmanApp &app, sf::RenderWindow *window);
	~ScoreBoard();
	Button* back;
	void HandleEvent(sf::Event event);
	void Draw(sf::RenderWindow &window);
private:
	sf::Text text;
	bool Init(sf::RenderWindow *window);
};

