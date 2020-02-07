#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>
class Actors
{
public:
	Actors();
	~Actors();
	virtual void AddFrames(thor::FrameAnimation& animation, int y, int xFirst, int xLast, float duration = 1.f);
	virtual bool Init();
	virtual void Update(sf::Time deltaTime);
	sf::Texture texture;
	sf::Sprite spritesheet;
	thor::Animator<sf::Sprite, std::string> *animator;
	float spaceHor = 12;
	float spaceVer = 36;
	sf::Vector2f currentPos; //col, row
	float moveGranularity = 16;
	virtual bool ValidMove(sf::Vector2i dir);
	bool ShouldComputeMove(sf::Vector2i dir);
	int(*pmGrid)[28][36];
	sf::Vector2i currentDir;
protected:	

	thor::FrameAnimation frameAnimations; 
	thor::AnimationMap<sf::Sprite, std::string> animations;
	float maxMoveGranularity;
	float moveAmmount;
	//float factor;
};

