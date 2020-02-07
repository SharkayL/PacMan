#include "BackGround.h"

BackGround::BackGround()
{
	Load();
}

BackGround::~BackGround()
{
}

bool BackGround::Load() {
	bgdTexture.loadFromFile("Resources/bgd.png");
	sprite.setTexture(bgdTexture);
	return true;
}
void BackGround::Draw(sf::RenderWindow &window) {
	window.draw(sprite);
}