#pragma once
#include <SFML/Graphics.hpp>

class BackGround
{
public:
	BackGround();
	~BackGround();
	void Draw(sf::RenderWindow &window);
private:
	sf::Texture bgdTexture;
	sf::Sprite sprite;
	bool Load();
};
