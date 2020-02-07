#include "GameOver.h"


GameOver::GameOver(PacmanApp &app, sf::RenderWindow *window) : Scene(app)
{
	Init(window);
	ScreenCapture();
}


GameOver::~GameOver()
{
}

bool GameOver::Init(sf::RenderWindow *window){
	this->window = window;
	win = true;
	texture.create(600, 800);
	yes = new Button(window, { 120, 400 }, { 120, 40 }, "/* Yes */");
	no = new Button(window, { 360, 400 }, { 120, 40 }, "/* No */");
	text.setFont(yes->font);
	text.setString("You win! Play again?");
	text.setCharacterSize(48);
	text.setPosition(80, 50);
	return true;
}

void GameOver::Update(sf::Time timeDelta) {
	if (win) {
		win = false;
	}
}
void GameOver::ScreenCapture() {
	texture.update(*window);
	picture.setTexture(texture);
}
void GameOver::Draw(sf::RenderWindow &window) {
	window.draw(picture);
	window.draw(text);
	yes->Draw(window);
	no->Draw(window);
}
void GameOver::HandleEvent(sf::Event event) {
	yes->HandleEvent(event);
	no->HandleEvent(event);
	if (yes->clicked) 
		play = true;
	if (no->clicked) window->close();
}