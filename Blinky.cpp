#include "Blinky.h"

Blinky::Blinky()
{
	Init();
}


Blinky::~Blinky()
{
}

bool Blinky::Init() {
	Actors::Init();
	currentPos = { 13.f, 13.f };
	currentDir = { -1, 0 };
	spritesheet.setOrigin({ 16, 16 });

	//spritesheet.setPosition({ iniPos.x * 16 + spaceHor, iniPos.y * 16 + spaceVer });
	thor::FrameAnimation left;
	AddFrames(left, 2, 4, 5);
	thor::FrameAnimation right;
	AddFrames(right, 2, 6, 7);
	thor::FrameAnimation up;
	AddFrames(up, 2, 0, 1);
	thor::FrameAnimation down;
	AddFrames(down, 2, 2, 3);

	animations.addAnimation("left", left, sf::seconds(0.35));
	animations.addAnimation("right", right, sf::seconds(0.35));
	animations.addAnimation("up", up, sf::seconds(0.35));
	animations.addAnimation("down", down, sf::seconds(0.35));
	animator = new thor::Animator< sf::Sprite, std::string>(animations);
	animator->play() << thor::Playback::loop("left");
	return true;
}
void Blinky::Update(sf::Time timeDelta) {
	animator->update(timeDelta);
	animator->animate(spritesheet);
	if (state == playing) {
		Playing();
		if (*chaseState == scatter)
			target = { 1, 3 };
		if (*chaseState == chase)
			target = pacman->currentPos;
	}
	if (state == frightened) {
		Frightened(timeDelta);
	}
	if (state == eaten) {
		Eaten();
	}
}

void Blinky::Draw(sf::RenderWindow &window) {
	sf::Vector2f spritePos = { currentPos.x * 16 + spaceHor, currentPos.y * 16 + spaceVer };
	spritesheet.setPosition(spritePos);
	window.draw(spritesheet);
}


