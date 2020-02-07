#include "Actors.h"
#include <iostream>
Actors::Actors()
{
}


Actors::~Actors()
{
}

bool Actors::Init() {
	texture.loadFromFile("Resources/spritesheet.png");
	spritesheet.setTexture(texture);
	spaceHor = 76+8;
	spaceVer = 112+8;
	maxMoveGranularity = 1.f / (moveGranularity + 1);
	return true;
}
void Actors::Update(sf::Time deltaTime) {
}
void Actors::AddFrames(thor::FrameAnimation& animation, int y, int xFirst, int xLast, float duration)
{
	const int step = (xFirst < xLast) ? +1 : -1;
	xLast += step;

	for (int x = xFirst; x != xLast; x += step)
		animation.addFrame(duration, sf::IntRect(32 * x, 32 * y, 32, 32));

}

bool Actors::ShouldComputeMove(sf::Vector2i dir) {
	if (dir.x != 0 && currentDir.x != 0 && dir.x != currentDir.x) {
		return true;
	}
	if (dir.y != 0 && currentDir.y != 0 && dir.y != currentDir.y) {
		return true;
	}
	if (currentDir.x != 0) {
		return ((int)round(currentPos.x * moveGranularity)) % 16 == 0;
	}
	if (currentDir.y != 0) {
		return ((int)round(currentPos.y * moveGranularity)) % 16 == 0;
	}
	return true;
}

bool Actors::ValidMove(sf::Vector2i dir) {
	if (dir.x == 0 && dir.y == 0) {
		return false;
	}
	int x = round(currentPos.x);
	int y = round(currentPos.y);
	int gridOffsetX = x+dir.x;
	int gridOffsetY = y+dir.y;
	if (gridOffsetX < 0 || gridOffsetY < 0) {
		if (gridOffsetY == 16) {
			return true;
		}
		return false;
	}
	if (gridOffsetX > 27) {
		if (gridOffsetY == 16) {
			return true;
		}
		return false;
	}
	if (gridOffsetY > 35) {
		return false;
	}
	int gridValue = (*pmGrid)[gridOffsetX][gridOffsetY];

	if (gridValue == 0 || gridValue == (int)'L' || gridValue == (int)'S') {
		return true;
	}
	return false;
}
//sf::Vector2f Actors::Interpolate(const sf::Vector2f& pointA, const sf::Vector2f& pointB, float factor) {
//	if (factor > 1.f) 
//		factor = 1.f;
//	else if (factor < 0)
//		factor = 0.f;
//
//	return pointA + (pointB - pointA) *factor;
//}
