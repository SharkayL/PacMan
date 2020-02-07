#include "Menu.h"

class PacmanApp;

Menu::Menu(PacmanApp &app,sf::RenderWindow *window) : Scene(app)
{
	Init(window);
}


Menu::~Menu()
{
}

bool Menu::Init(sf::RenderWindow *window) {

	start = new Button(window,{ 185, 400 }, { 230, 40 }, "/* Play Game */");
	score = new Button(window,{ 185, 500 }, { 230, 40 }, "/* High Score */");
	title.setFont(start->font);
	title.setString("PACMAN");
	title.setCharacterSize(48);
	title.setPosition(200, 50);
	return true;
}
void Menu::Draw(sf::RenderWindow &window) {
	Scene::Draw(window);
	start->Draw(window);
	score->Draw(window);
	window.draw(title);
}
void Menu::HandleEvent(sf::Event event) {
	start->HandleEvent(event);
	score->HandleEvent(event);
	if (start->clicked) {
		play = true;
		menu = false;
	}
	if (score->clicked) {
		displayScore = true;
		menu = false;
	}
}