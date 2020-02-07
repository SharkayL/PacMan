#pragma once
#include "SFML/Graphics.hpp"
using namespace std;

struct dot {
	int row;
	int col;
	sf::Sprite sprite;
};
class Dots
{
public:
	Dots();
	~Dots();
	sf::Texture s;
	sf::Texture l;
	sf::Sprite dotSprite;
	sf::Sprite pelletSprite;
	//vector<dot> dots;
	int(* pmGrid)[28][36];
	void Draw(sf::RenderWindow &window);
	bool Init();
	int countDots;
};

