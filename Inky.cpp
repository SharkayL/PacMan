#include "Inky.h"



Inky::Inky()
{
	Init();
}


Inky::~Inky()
{
}
bool Inky::Init() {
	Actors::Init();
	atHome = true;
	currentPos = { 15.f, 16.f };
	spritesheet.setOrigin({ 16, 16 });
	//spritesheet.setPosition({ iniPos.x * 16.f + spaceHor, iniPos.y * 16 + spaceVer });
	thor::FrameAnimation left;
	AddFrames(left, 4, 4, 5);
	thor::FrameAnimation right;
	AddFrames(right, 4, 6, 7);
	thor::FrameAnimation up;
	AddFrames(up, 4, 0, 1);
	thor::FrameAnimation down;
	AddFrames(down, 4, 2, 3);

	animations.addAnimation("left", left, sf::seconds(0.35));
	animations.addAnimation("right", right, sf::seconds(0.35));
	animations.addAnimation("up", up, sf::seconds(0.35));
	animations.addAnimation("down", down, sf::seconds(0.35));
	animator = new thor::Animator< sf::Sprite, std::string>(animations);
	animator->play() << thor::Playback::loop("up");
	return true;
}
void Inky::Update(sf::Time timeDelta) {
	animator->update(timeDelta);
	animator->animate(spritesheet);
	if (state == playing) {
		Playing();
		if (*chaseState == scatter)
			target = { 26, 3 };
		if (*chaseState == chase) {
			sf::Vector2f pm = { pacman->currentPos.x + pacman->currentDir.x * 2, pacman->currentPos.y + pacman->currentDir.y * 2 };
			target = { pm.x - (blinkyPos->x - pm.x), pm.y - (blinkyPos->y - pm.y) };
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

void Inky::Draw(sf::RenderWindow &window) {
	sf::Vector2f spritePos = { currentPos.x * 16 + spaceHor, currentPos.y * 16 + spaceVer };
	spritesheet.setPosition(spritePos);
	window.draw(spritesheet);
}

