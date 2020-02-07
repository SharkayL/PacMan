#include "PacmanApp.h"
#include "Game.h"
#include "Menu.h"
#include "GameOver.h"
#include "ScoreBoard.h"


PacmanApp::PacmanApp(){
	windowWidth = 600;
	windowHeight = 800;
	window.create(
		sf::VideoMode(windowWidth, windowHeight, 32), "Pacman", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
	view = window.getDefaultView();
	currentScene = new Menu(*this,&this->window);
	//currentScene = new Game(*this);
}


PacmanApp::~PacmanApp()
{
}

void PacmanApp::Run() {
	while (window.isOpen()) {
		//sf::Time elapsedTime = frameClock.restart();
		while (window.pollEvent(event)) {
			currentScene->HandleEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
			if (currentScene->play) {
				currentScene = new Game(*this);
				currentScene->play = false;
			}
			if (currentScene->displayScore) {
				currentScene = new ScoreBoard(*this, &this->window);
			}
			if (currentScene->menu) {
				currentScene = new Menu(*this, &this->window);
			}
		}
		Update();
		window.clear();
		Draw();
	} 
}

void PacmanApp::Draw() {
	window.clear();
	currentScene->Draw(window);
	window.display();
}
void PacmanApp::Update() {
	sf::Time timeDelta = frameClock.restart();
	currentScene->Update(timeDelta);
	if (currentScene->win) {
		currentScene = new GameOver(*this, &this->window);
	}
}