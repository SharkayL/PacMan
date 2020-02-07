#pragma once
#include "Ghosts.h"
class Inky : public Ghosts
{
public:
	Inky();
	~Inky();
	bool Init();
	void Update(sf::Time timeDelta) override;
	void Draw(sf::RenderWindow &window);
	sf::Vector2f* blinkyPos;
};

