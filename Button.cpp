#include "Button.h"



Button::Button(sf::RenderWindow *window, sf::Vector2f pos, sf::Vector2f size, sf::String buttonText)
{
	clicked = false;
	this->window = window;
	rectButton.setPosition(pos);
	rectButton.setSize(size);
	rectButton.setFillColor(sf::Color::Transparent);
	rectButton.setOutlineThickness(5);
	bound = rectButton.getGlobalBounds();
	font.loadFromFile("Resources/sansation.ttf");
	this->buttonText.setFont(font);
	this->buttonText.setString(buttonText);
	this->buttonText.setCharacterSize(32);
	this->buttonText.setFillColor(sf::Color::Yellow);
	sf::FloatRect Textbound = this->buttonText.getGlobalBounds();
	this->buttonText.setPosition(pos);
}


Button::~Button()
{
}

void Button::Draw(sf::RenderWindow &window) {
	window.draw(rectButton);
	window.draw(buttonText);
}
void Button::HandleEvent(sf::Event event) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		auto mousePos = sf::Mouse::getPosition(*window);
		if (mousePos.x >= bound.left &&
			mousePos.x <= bound.left + bound.width &&
			mousePos.y >= bound.top &&
			mousePos.y <= bound.top + bound.height) {
			clicked = true;
		}
	}
}