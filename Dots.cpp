#include "Dots.h"


Dots::Dots()
{
}

Dots::~Dots()
{
}

bool Dots::Init() {
	s.loadFromFile("Resources/Dot_S.png");
	l.loadFromFile("Resources/Dot_L.png");

	pelletSprite.setTexture(l);
	dotSprite.setTexture(s);
	countDots = 500;
	return true;
}
void Dots::Draw(sf::RenderWindow &window) {
	for (int row = 0; row < 36; ++row) {
		for (int col = 0; col < 28; ++col) {
			if ((*pmGrid)[col][row] == (int)'L') {
				pelletSprite.setPosition(col * 16 + 76, row * 16 + 112);
				window.draw(pelletSprite);
				++countDots;
			}
			else if ((*pmGrid)[col][row] == (int)'S') {
				dotSprite.setPosition(col * 16 + 76, row * 16 + 112);
				window.draw(dotSprite);
				++countDots;
			}
		}
	}
}

