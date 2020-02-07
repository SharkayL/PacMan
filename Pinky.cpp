#include "Pinky.h"



Pinky::Pinky()
{
	Init();
}


Pinky::~Pinky()
{
}
bool Pinky::Init() {
	Actors::Init();
	currentPos = { 11.f, 16.f };
	spritesheet.setOrigin({ 16, 16 });
	atHome = true;
	thor::FrameAnimation left;
	AddFrames(left, 3, 4, 5);
	thor::FrameAnimation right;
	AddFrames(right, 3, 6, 7);
	thor::FrameAnimation up;
	AddFrames(up, 3, 0, 1);
	thor::FrameAnimation down;
	AddFrames(down, 3, 2, 3);

	animations.addAnimation("left", left, sf::seconds(0.35));
	animations.addAnimation("right", right, sf::seconds(0.35));
	animations.addAnimation("up", up, sf::seconds(0.35));
	animations.addAnimation("down", down, sf::seconds(0.35));
	animator = new thor::Animator< sf::Sprite, std::string>(animations);
	animator->play() << thor::Playback::loop("up");
	return true;
}
void Pinky::Update(sf::Time timeDelta) {
	animator->update(timeDelta);
	animator->animate(spritesheet);
	if (state == playing) {
		Playing();
		if (*chaseState == scatter) 
			target = { 1, 31 };
		if (*chaseState == chase)
			target = { pacman->currentPos.x + pacman->currentDir.x * 2, pacman->currentPos.y + pacman->currentDir.y * 2 };
	}
	if (state == frightened) {
		Frightened(timeDelta);
	}
	if (state == eaten) {
		Eaten();
	}
	if (atHome) {
		if (round(currentPos.x) == 13) {
			currentPos.x = 13;
			atHome = false;
			leavingHome = true;
		}
	}
	if (leavingHome) {
		if (round(currentPos.y) == 13) {
			currentPos.y = 13;
			leavingHome = false;
		}
	}
}

void Pinky::Draw(sf::RenderWindow &window) {
	sf::Vector2f spritePos = { currentPos.x * 16 + spaceHor, currentPos.y * 16 + spaceVer };
	spritesheet.setPosition(spritePos);
	window.draw(spritesheet);
}

