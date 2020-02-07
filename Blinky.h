#pragma once
#include "Ghosts.h"
class Blinky : public Ghosts
{
public:
	Blinky();
	~Blinky();
	bool Init();
	void Update(sf::Time timeDelta) override;
	//void Scatter() override;
	//void Chase() override;
	void Draw(sf::RenderWindow &window);
};

