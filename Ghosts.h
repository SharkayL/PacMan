#pragma once
#include "Actors.h"
#include <array>
#include "ChaseStates.h"
#include "Pacman.h"


enum GhostStates {playing, eaten, frightened};
static int scoreCount;
class Ghosts : public Actors
{
public:
	Ghosts();
	~Ghosts();
	GhostStates state;
	ChaseStates* chaseState;
	Pacman* pacman;
	int* score;
	virtual void Update(sf::Time deltaTime) override;
	void Scatter();
	void Chase();
	void Playing();
	void Eaten();
	void Frightened(sf::Time deltaTime);
	void MakeFrightened();
	sf::Vector2i RandGenerator(std::array<sf::Vector2i, 3> directions);
	std::vector<sf::Vector2i> ValidDirections();
	std::array<sf::Vector2i, 3> PossibleDirections();
	sf::Vector2i TargetClosest(sf::Vector2f target);
	float AproxDistance(sf::Vector2i direction, sf::Vector2f destination);
	virtual void Move(sf::Time timeDelta);
	bool Init() override;
	bool goingHome;
	bool leavingHome;
	bool leavingFright;
	bool atHome;

protected:
	float speed;
	sf::Vector2f target;
	float distance;
	float countdown; 

};

