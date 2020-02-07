#pragma once
#include <SFML/Graphics.hpp>
class Fruits
{
public:
	Fruits();
	~Fruits();
	sf::Sprite cherry;
	sf::Sprite strawberry;
	sf::Sprite Orange;
	sf::Sprite pretzel;
	sf::Sprite apple;
	sf::Sprite pear;
	sf::Sprite banana;
	sf::Sprite points5;

	void Draw(sf::RenderWindow &window);
private:
	sf::Texture spritesheet;
	bool Init();
};

