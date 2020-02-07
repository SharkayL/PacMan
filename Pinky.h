#pragma once
#include "Ghosts.h"


class Pinky : public Ghosts
{
public:
	Pinky();
	~Pinky();
	bool Init();
	void Update(sf::Time timeDelta) override;
	void Draw(sf::RenderWindow &window);
};

