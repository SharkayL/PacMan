#pragma once
#include "Button.h"
#include "Scene.h"
class Menu : public Scene
{
public:
	Menu(PacmanApp &app,sf::RenderWindow *window);
	~Menu();
	void Draw(sf::RenderWindow &window);
	void HandleEvent(sf::Event event) override;
private:
	bool Init(sf::RenderWindow *window);
	Button* start;
	Button* score;
	sf::Text title;
};

