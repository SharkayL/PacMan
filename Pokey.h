#pragma once
#include "Ghosts.h"
class Pokey : public Ghosts
{
public:
	Pokey();
	~Pokey();
	bool Init();
	void Update(sf::Time timeDelta) override;
	void Draw(sf::RenderWindow &window);
};

