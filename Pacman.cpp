#include "Pacman.h"
#include <iostream>
Pacman::Pacman()
{
	Init();
}


Pacman::~Pacman()
{
}

bool Pacman::Init() {
	Actors::Init();
	currentPos = { 14,25 };
	speed = 100.f;
	currentDir = { -1, 0 };
	spritesheet.setOrigin({ 16, 16 });
	//spritesheet.setPosition();
	thor::FrameAnimation left;
	AddFrames(left, 0, 6, 7);
	AddFrames(left, 0, 6, 6);
	AddFrames(left, 1, 0, 0);
	thor::FrameAnimation right;
	AddFrames(right, 1, 1, 2);
	AddFrames(right, 1, 1, 1);
	AddFrames(right, 1, 3, 3);
	thor::FrameAnimation up;
	AddFrames(up, 0, 0, 1);
	AddFrames(up, 0, 0, 0);
	AddFrames(up, 0, 2, 2);
	thor::FrameAnimation down;
	AddFrames(down, 0, 3, 4);
	AddFrames(down, 0, 3, 3);
	AddFrames(down, 0, 5, 5);
	animations.addAnimation("left", left, sf::seconds(0.35));
	animations.addAnimation("right", right, sf::seconds(0.35));
	animations.addAnimation("up", up, sf::seconds(0.35));
	animations.addAnimation("down", down, sf::seconds(0.35));
	animator = new thor::Animator< sf::Sprite, std::string>(animations);
	animator->play() << thor::Playback::loop("left");
	//bool busy = false;
	//auto lambdaAnimator = animator;
	//auto onDone = [&busy, lambdaAnimator]()
	//{
	//	busy = false;
	//	lambdaAnimator->queue() << thor::Playback::loop("left");
	//};
	return true;
}
void Pacman::Update(sf::Time timeDelta) {
	animator->update(timeDelta);
	animator->animate(spritesheet);
}

void Pacman::Draw(sf::RenderWindow &window) {
	sf::Vector2f spritePos = { currentPos.x * 16 + spaceHor, currentPos.y * 16 + spaceVer };
	spritesheet.setPosition(spritePos);
	window.draw(spritesheet);
}

void Pacman::Move(sf::Vector2i dir, sf::Time timeDelta) {
	moveAmmount = timeDelta.asSeconds() * (speed / moveGranularity);
	for (float moveFraction = std::min(moveAmmount, maxMoveGranularity); moveAmmount > 0; moveAmmount -= maxMoveGranularity) {

		if (ShouldComputeMove(dir)) {
			if (ValidMove(dir)) {
				if (dir != currentDir) {
					if (dir.x == 1) {
						animator->play() << thor::Playback::loop("right");
					}
					else if (dir.x == -1) {
						animator->play() << thor::Playback::loop("left");
					}
					else if (dir.y == 1) {
						animator->play() << thor::Playback::loop("down");
					}
					else if (dir.y == -1) {
						animator->play() << thor::Playback::loop("up");
					}
				}

				currentDir = dir;
			}
			else if (!ValidMove(currentDir)) {
				currentDir = { 0,0 };
			}
			//Round out fractional movements when moving on opposite axis
			if (currentDir.x != 0) {
				currentPos.y = round(currentPos.y);
			}
			if (currentDir.y != 0) {
				currentPos.x = round(currentPos.x);
			}
		}

		sf::Vector2f moveBy = { currentDir.x * moveFraction,currentDir.y * moveFraction };
		currentPos += moveBy;
		if (round(currentPos.y) == 16) {
			if (round(currentPos.x) <= 0 && currentDir.x == -1) {
				currentPos.x = 27.5;
			}
			else if (round(currentPos.x) >= 27 && currentDir.x == 1) {
				currentPos.x = -0.5;
			}
		}
	}
}

