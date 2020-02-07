#pragma once
#include <SFML/Graphics.hpp>
class Button
{
public:
	Button(sf::RenderWindow *window, sf::Vector2f pos, sf::Vector2f size, sf::String buttonText);
	~Button();
	void Draw(sf::RenderWindow &window);
	sf::FloatRect bound;
	sf::Font font;
	void HandleEvent(sf::Event event);
	bool clicked;
private:
	sf::RenderWindow *window;
	sf::RectangleShape rectButton;
	sf::Text buttonText;
};

