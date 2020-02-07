#pragma once
#include "Scene.h"
#include "Button.h"
class GameOver : public Scene
{
public:
	GameOver(PacmanApp &app, sf::RenderWindow *window);
	~GameOver();
	void Update(sf::Time timeDelta) override;
	void ScreenCapture();
	void Draw(sf::RenderWindow &window);
	void HandleEvent(sf::Event) override;
	int* score;
private:
	sf::Texture texture;
	sf::Sprite picture;
	sf::RenderWindow *window;
	bool Init(sf::RenderWindow *window);
	Button* yes;
	Button* no;
	sf::Text text;
};

