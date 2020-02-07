#pragma once
#include "Actors.h"
class Pacman : public Actors
{
public:
	Pacman();
	~Pacman();
	void Update(sf::Time timeDelta) override;
	void Draw(sf::RenderWindow &window);
	bool keepGoing;
	bool Init() override;
	void Move(sf::Vector2i dir, sf::Time timeDelta);
private:
	float speed;
	bool move;
};

