#include "Game.h"
#include <fstream>
#include <sstream>
#include <iostream>


Game::Game(PacmanApp &app) : Scene(app)
{
	Init();
}


Game::~Game()
{
}

void Game::HandleEvent(sf::Event event) {
	using Key = sf::Keyboard::Key;
	auto keyDown = [](sf::Keyboard::Key k) {
		return sf::Keyboard::isKeyPressed(k);
	};

	if (keyDown(Key::Up)) {
		dir.x = 0;
		dir.y = -1;
	}
	if (keyDown(Key::Down)) {
		dir.x = 0;
		dir.y = 1;
	}
	if (keyDown(Key::Left)) {
		dir.x = -1;
		dir.y = 0;
	}
	if (keyDown(Key::Right)) {
		dir.x = 1;
		dir.y = 0;
	}
}

bool Game::Init() {
	ifstream data("maze.txt");
	string line;
	if (data.is_open())
	{
		int posIndex = 0;
		while (getline(data, line)) {
			std::istringstream lineStream(line);
			string token;
			while (getline(lineStream, token, ',')) {
				if (token == "\n") {
					continue;
				}
				int x = posIndex % 28;
				int y = posIndex / 28;
				int tileId = stoi(token);
				pmGrid[x][y] = tileId;
				++posIndex;
			}
		}
		data.close();
	}
	else printf_s("unable to open maze.txt");

	dots.pmGrid = &this->pmGrid;
	dots.Init();
	pacman.pmGrid = &this->pmGrid;
	dir = { -1, 0 };
	blinky.chaseState = &this->gameStates;
	blinky.pacman = &this->pacman;
	blinky.pmGrid = &this->pmGrid;
	blinky.score = &this->score;
	pinky.chaseState = &this->gameStates;
	pinky.pacman = &this->pacman;
	pinky.pmGrid = &this->pmGrid;
	pinky.score = &this->score;
	inky.chaseState = &this->gameStates;
	inky.pacman = &this->pacman;
	inky.pmGrid = &this->pmGrid;
	inky.blinkyPos = &this->blinky.currentPos;
	inky.score = &this->score;
	pokey.chaseState = &this->gameStates;
	pokey.pacman = &this->pacman;
	pokey.pmGrid = &this->pmGrid;
	pokey.score = &this->score;
	font.loadFromFile("Resources/sansation.ttf");
	scoreText.setFont(font);
	scoreText.setPosition(80, 650);
	cherry = fruits.cherry;
	gotBonus = false;
	return true;
}
void Game::Update(sf::Time timeDelta) {
	elapseTime += timeDelta;
	orderTimer += timeDelta;
	switch (gameStates)
	{
	case scatter: Scatter();
		break;
	case chase: Chase();
		break;
	}
	pacman.Update(timeDelta);
	blinky.Update(timeDelta);
	pinky.Update(timeDelta);
	inky.Update(timeDelta);
	pokey.Update(timeDelta);
	pacman.Move(dir, timeDelta);
	if (pmGrid[(int)round(pacman.currentPos.x)][(int)round(pacman.currentPos.y)] == 'L') {
		blinky.MakeFrightened();
		pinky.MakeFrightened();
		inky.MakeFrightened();
		pokey.MakeFrightened();
		score += 50;
	}
	if (pmGrid[(int)round(pacman.currentPos.x)][(int)round(pacman.currentPos.y)] == 'S') {
		score += 10;
	}
	if (round(pacman.currentPos.x) > 0 && round(pacman.currentPos.y) >= 3
		&& round(pacman.currentPos.x) < 27 && round(pacman.currentPos.y) <= 32) {
		pmGrid[(int)round(pacman.currentPos.x)][(int)round(pacman.currentPos.y)] = 0;
	}
	blinky.Move(timeDelta);
	pinky.Move(timeDelta);
	if (orderTimer >= sf::seconds(1))
		inky.Move(timeDelta);
	if (orderTimer >= sf::seconds(2))
		pokey.Move(timeDelta);
	ScoreText();
	if (orderTimer > sf::seconds(20) && orderTimer <= sf::seconds(30) && gotBonus == false) {
		bonus = true;
		if (round(pacman.currentPos.y) == 19 && (round(pacman.currentPos.x) == 13 || round(pacman.currentPos.x) == 14)) {
			bonus = false;
			gotBonus = true;
			score += 500;
		}
	}
	else bonus = false;
	if (dots.countDots == 0) {
		win = true;
		play = false;
		finalScore.finalScore = score;
		finalScore.UpdatingScores();
	}
	else dots.countDots = 0;
}
void Game::Draw(sf::RenderWindow &window) {
	Scene::Draw(window);
	dots.Draw(window);
	pacman.Draw(window);
	blinky.Draw(window);
	pinky.Draw(window);
	inky.Draw(window);
	pokey.Draw(window);
	window.draw(scoreText);
	fruits.Draw(window);
	if (bonus) {
		(cherry).setPosition(284, 408);
		window.draw(cherry);
	}
}
void Game::Scatter() {
	if (elapseTime.asSeconds() >= 7) {
		gameStates = chase;
		elapseTime = sf::Time::Zero;
	}
}
void Game::Chase() {
	if (elapseTime.asSeconds() >= 20) {
		gameStates = scatter;
		elapseTime = sf::Time::Zero;
	}
}
void Game::ScoreText() {
	char buff[32];
	sprintf_s(buff, "Score: %i", score);
	scoreText.setString(buff);
}
