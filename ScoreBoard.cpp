#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(PacmanApp &app, sf::RenderWindow *window) : Scene(app)
{
	Init(window);
}


ScoreBoard::~ScoreBoard()
{
}

bool ScoreBoard::Init(sf::RenderWindow *window) {
	back = new Button(window, { 225, 580 }, { 150, 40 }, "/* Back */"); 
	text.setFont(back->font);
	string st;
	int n = 0;
	for (auto ite = scores.begin(); ite != scores.end(); ++ite) {
		st += (to_string(++n) + ". " + to_string(*ite)+'\n');
	}
	text.setString(st);
	text.setCharacterSize(54);
	text.setPosition(200, 200);
	return true;
}
void ScoreBoard::HandleEvent(sf::Event event){
	back->HandleEvent(event);
	if (back->clicked) {
		displayScore = false;
		menu = true;
	}
}
void ScoreBoard::Draw(sf::RenderWindow& window) {
	Scene::Draw(window);
	back->Draw(window);
	window.draw(text);
}