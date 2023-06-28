#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox
{
private:
	sf::Text textbox;
	std::ostringstream text;
	sf::Text LabelText;
	std::string LText;
	sf::Color inputTextColor;
	sf::Color labelTextColor = sf::Color::Red;
	bool is_selected = false;
	bool hasLimit = true;
	int limit = 10;
	int positionX = 0;
	int positionY = 0;
	int inputFontSize = 15;
	int labelFontSize = 15;

	void inputLogic(int charTyped);
	void deleteLastChar();

public:
	Textbox(int px, int py, int fontSize, sf::Color Color, bool sel);

	void setLabel(std::string text, sf::Color color, int Size);

	void setFont(sf::Font& font);

	void setPosition(sf::Vector2f pos);

	void setLimit(bool ToF);

	void setLimit(bool ToF, int lim);

	void setSelected(bool sel);

	std::string getText();

	void drawTo(sf::RenderWindow& window);
	void typedOn(sf::Event input);

	bool isMouseOver(sf::RenderWindow& window);

};

