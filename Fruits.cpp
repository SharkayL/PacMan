#include "Fruits.h"



Fruits::Fruits()
{
	Init();
}


Fruits::~Fruits()
{
}

bool Fruits::Init() {
	spritesheet.loadFromFile("Resources/spritesheet.png");
	cherry.setTexture(spritesheet);
	cherry.setTextureRect(sf::IntRect(0, 6 * 32, 32, 32));
	cherry.setPosition(480, 650);
	return true;
}
void Fruits::Draw(sf::RenderWindow &window) {
	window.draw(cherry);
}
