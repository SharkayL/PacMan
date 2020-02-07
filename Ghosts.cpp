#include "Ghosts.h"

Ghosts::Ghosts()
{
	Init();
}


Ghosts::~Ghosts()
{
}

void Ghosts::Update(sf::Time deltaTime) {
	switch (state)
	{
	case playing: Playing();
		break;
	case eaten: Eaten();
		break;
	case frightened: Frightened(deltaTime);
		break;
	}

}
void Ghosts::Playing() {
	speed = 100.f;
	if (*chaseState == scatter) Scatter();
	if (*chaseState == chase) Chase();

}
void Ghosts::Eaten() {
	speed = 200.f;
	target = { 13.f, 13.f }; //down 3*16;
	if (round(currentPos.x) == 13 && round(currentPos.y) == 13) {
		if (currentDir.y != -1) {
			target = { 13.f, 16.f };
			goingHome = true;
		}
		if (currentDir.y == -1) {
			state = playing;
			leavingHome = false;
		}
	}
	if (round(currentPos.x) == 13 && round(currentPos.y) == 16) {
		target = { 13.f, 13.f };
		leavingHome = true;
		goingHome = false;
	}
	if (currentDir.x == 1) {
		animator->play() << thor::Playback::loop("eyeRight");
	}
	else if (currentDir.x == -1) {
		animator->play() << thor::Playback::loop("eyeLeft");
	}
	else if (currentDir.y == 1) {
		animator->play() << thor::Playback::loop("eyeDown");
	}
	else if (currentDir.y == -1) {
		animator->play() << thor::Playback::loop("eyeUp");
	}
}
void Ghosts::Frightened(sf::Time deltaTime) {
	speed = 60.f;
	float col = rand() % 26;
	float row = rand() % 29;
	target = { 1+col, 29+row };
	if (countdown < 1 && !leavingFright) {
		leavingFright = true;
		animator->play() << thor::Playback::loop("white");
	}
	if (countdown > 0) countdown -= deltaTime.asSeconds();
	else {
		state = playing;
		countdown = 8.f;
		scoreCount = 0;
	}
	if (sqrt(powf(currentPos.x - pacman->currentPos.x, 2) + powf(currentPos.y - pacman->currentPos.y, 2)) <= 2) {
		++scoreCount;
		if (scoreCount > 4) {
			scoreCount = 1;
		}
		(*score) += scoreCount * 200;
		//std::cout << *score << std::endl;
		state = eaten;
	}
}

void Ghosts::MakeFrightened() {
	if (state != frightened) {
		currentDir = { -currentDir.x,-currentDir.y };
	}
	state = frightened;
	countdown = 10.f;
	leavingFright = false;
	animator->play() << thor::Playback::loop("blue");
}

void Ghosts::Scatter() {

}

void Ghosts::Chase() {

}

std::array<sf::Vector2i, 3> Ghosts::PossibleDirections() {
	if (currentDir == sf::Vector2i(-1, 0)) { //x 
		return { sf::Vector2i(0, -1),sf::Vector2i(-1, 0),sf::Vector2i(0, 1) };
	}
	if (currentDir == sf::Vector2i(0, 1)) { //y
		return { sf::Vector2i(-1, 0),sf::Vector2i(0, 1),sf::Vector2i(1, 0) };
	}  
	if (currentDir == sf::Vector2i(1, 0)) {
		return { sf::Vector2i(0, -1),sf::Vector2i(0, 1),sf::Vector2i(1, 0) };
	}	
	return { sf::Vector2i(0,-1),sf::Vector2i(-1,0),sf::Vector2i(1, 0) };
}

float Ghosts::AproxDistance(sf::Vector2i direction, sf::Vector2f destination) {
	float x = currentPos.x + direction.x - destination.x;
	float y = currentPos.y + direction.y - destination.y;
	return x * x + y * y;
}

sf::Vector2i Ghosts::TargetClosest(sf::Vector2f target) {
	if (goingHome) { 
		return { 0, 1 }; 
	}
	if (leavingHome) {
		return { 0, -1 };
	}
	if (atHome) {
		if (currentPos.x < 13) {
			return { 1, 0 };
		}
		else if (currentPos.x > 13) {
			return { -1, 0 };
		}
	}
	else if (round(currentPos.y) == 16) {
		if (round(currentPos.x) <= 0 && currentDir.x == -1) {
			currentPos.x = 27;
		}
		else if (round(currentPos.x) >= 27 && currentDir.x == 1) {
			currentPos.x = 0;
		}
	}
	auto validDirections = ValidDirections();
	auto selectedDirection = validDirections[0];
	if (validDirections.size() == 1) {
		return selectedDirection;
	}
	if (validDirections.size() == 0) {
		return {-currentDir.x, -currentDir.y};
	}
	float length = AproxDistance(validDirections[0], target);	
	for (auto ite = ++validDirections.begin(); ite != validDirections.end(); ++ite) {
		auto checkedDirection = *ite;
		float checkDist = AproxDistance(checkedDirection, target);
		if (checkDist < length) {
			length = checkDist;
			selectedDirection = checkedDirection;
		}
	}
	return selectedDirection;
}

std::vector<sf::Vector2i> Ghosts::ValidDirections() {
	auto directions = PossibleDirections();
	std::vector<sf::Vector2i> validDirections;
	for (auto ite = directions.begin(); ite != directions.end(); ++ite) {
		auto direction = *ite;
		if (ValidMove(direction)) {
			validDirections.push_back(direction);
		}
	}
	return validDirections;
}

sf::Vector2i Ghosts::RandGenerator(std::array<sf::Vector2i, 3> directions) { //frightened state	
	srand(time(NULL));
	auto dirs = ValidDirections();
	int size = dirs.size();
	if (dirs.size() == size) {
		return dirs[0];
	}
	int random = rand() % size;
	return dirs[random];
}

void Ghosts::Move(sf::Time timeDelta) {
	moveAmmount = timeDelta.asSeconds() * (speed / (moveGranularity+1));
	bool computedMove = false;
	for (float moveFraction = std::min(moveAmmount, maxMoveGranularity); moveAmmount > 0; moveAmmount -= maxMoveGranularity) {
		if (ShouldComputeMove(currentDir)) {
			if (!computedMove) {
				computedMove = true;
				auto selectedDirection = TargetClosest(target);
				if (selectedDirection != currentDir) {
					if (selectedDirection.x == 1) {
						if (state == playing)
							animator->play() << thor::Playback::loop("right");
					}
					else if (selectedDirection.x == -1) {
						if (state == playing)
							animator->play() << thor::Playback::loop("left");
					}
					else if (selectedDirection.y == 1) {
						if (state == playing)
							animator->play() << thor::Playback::loop("down");
					}
					else if (selectedDirection.y == -1) {
						if (state == playing)
							animator->play() << thor::Playback::loop("up");
					}

					currentDir = selectedDirection;
				}

			}
		}
		else {
			computedMove = false;
		}
		if (currentDir.x != 0) {
			currentPos.y = round(currentPos.y);
		}
		if (currentDir.y != 0) {
			currentPos.x = round(currentPos.x);
		}

		sf::Vector2f moveBy = { currentDir.x * moveFraction,currentDir.y * moveFraction };
		currentPos += moveBy;
	}
}
bool Ghosts::Init() {
	goingHome = false;
	leavingHome = false;
	atHome = false;
	leavingFright = false;
	scoreCount = 0;

	thor::FrameAnimation blue;
	AddFrames(blue, 1, 4, 5);
	thor::FrameAnimation white;
	AddFrames(white, 1, 4, 7);
	thor::FrameAnimation eyeUp;
	AddFrames(eyeUp, 7, 4, 4);
	thor::FrameAnimation eyeDown;
	AddFrames(eyeDown, 7, 5, 5);
	thor::FrameAnimation eyeLeft;
	AddFrames(eyeLeft, 7, 6, 6);
	thor::FrameAnimation eyeRight;
	AddFrames(eyeRight, 7, 7, 7);

	animations.addAnimation("blue", blue, sf::seconds(0.35));
	animations.addAnimation("white", white, sf::seconds(0.35));
	animations.addAnimation("eyeUp", eyeUp, sf::seconds(1));
	animations.addAnimation("eyeDown", eyeDown, sf::seconds(1));
	animations.addAnimation("eyeLeft", eyeLeft, sf::seconds(1));
	animations.addAnimation("eyeRight", eyeRight, sf::seconds(1));
	animator = new thor::Animator< sf::Sprite, std::string>(animations);
	return true;
}
