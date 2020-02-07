#include "Pokey.h"



Pokey::Pokey()
{
	Init();
}


Pokey::~Pokey()
{
}

bool Pokey::Init() {
	Actors::Init();
	currentPos = { 13.f, 16.f };
	atHome = true;
	spritesheet.setOrigin({ 16, 16 });
	thor::FrameAnimation left;
	AddFrames(left, 5, 4, 5);
	thor::FrameAnimation right;
	AddFrames(right, 5, 6, 7);
	thor::FrameAnimation up;
	AddFrames(up, 5, 0, 1);
	thor::FrameAnimation down;
	AddFrames(down, 5, 2, 3);

	animations.addAnimation("left", left, sf::seconds(0.35));
	animations.addAnimation("right", right, sf::seconds(0.35));
	animations.addAnimation("up", up, sf::seconds(0.35));
	animations.addAnimation("down", down, sf::seconds(0.35));
	animator = new thor::Animator< sf::Sprite, std::string>(animations);
	animator->play() << thor::Playback::loop("up");
	return true;
}
void Pokey::Update(sf::Time timeDelta) {
	animator->update(timeDelta);
	animator->animate(spritesheet);
	if (state == playing) {
		Playing();
		if (*chaseState == scatter)
			target = { 26, 31 };
		if (*chaseState == chase) {
			sf::Vector2f pm = { pacman->currentPos.x + pacman->currentDir.x * 2, pacman->currentPos.y + pacman->currentDir.y * 2 };
			if (currentPos.x - pm.x <= 8 || currentPos.y - pm.y <= 8) {
				target = pm;
			}
			else target = { 26, 31 };
		}
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

void Pokey::Draw(sf::RenderWindow &window) {
	sf::Vector2f spritePos = { currentPos.x * 16 + spaceHor, currentPos.y * 16 + spaceVer };
	spritesheet.setPosition(spritePos);
	window.draw(spritesheet);
}
