#include "Textbox.h"


Textbox::Textbox(int px, int py, int fontSize, sf::Color Color, bool sel) {
	positionX = px;
	positionY = py;
	inputFontSize = fontSize;
	inputTextColor = Color;

	is_selected = sel;
	if (sel) {
		textbox.setString("_");
	}
	else {
		textbox.setString("");
	}

}

void Textbox::setLabel(std::string text, sf::Color color, int Size) {
	labelFontSize = Size;
	labelTextColor = color;
	LText = text;
}

void Textbox::setFont(sf::Font& font) {
	textbox.setFont(font);
}

void Textbox::setPosition(sf::Vector2f pos) {
	textbox.setPosition(pos);
}

void Textbox::setLimit(bool ToF) {
	hasLimit = ToF;
}

void Textbox::setLimit(bool ToF, int lim) {
	hasLimit = ToF;
	limit = lim;
}

void Textbox::setSelected(bool sel) {
	is_selected = sel;
	if (!sel) {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length(); i++) {
			newT += t[i];
		}
		textbox.setString(newT);
	}
}

std::string Textbox::getText() {
	return text.str();
}

void Textbox::drawTo(sf::RenderWindow& window) {

	sf::Font font;
	font.loadFromFile("Roboto-Bold.ttf");
	textbox.setFont(font);
	textbox.setCharacterSize(inputFontSize);
	textbox.setColor(inputTextColor);
	textbox.setPosition(sf::Vector2f(positionX, positionY));

	LabelText.setFont(font);
	LabelText.setString(LText);
	LabelText.setColor(labelTextColor);
	LabelText.setCharacterSize(labelFontSize);
	LabelText.setPosition(sf::Vector2f(positionX, positionY - (labelFontSize + 5)));

	// define a label text
	//

	// define a rectangle to select Input
	sf::RectangleShape rectangle(sf::Vector2f(120, 50));
	// create input shape as border
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(1.0);
	// change the size to 250x font Size + 10px;
	int inputHeight = textbox.getCharacterSize() + 10;
	int inputWidth = 250;
	sf::Vector2f inputPos = textbox.getPosition();
	rectangle.setSize(sf::Vector2f(inputWidth, inputHeight));
	rectangle.setPosition(inputPos);


	window.draw(rectangle);
	window.draw(LabelText);
	window.draw(textbox);
}

void Textbox::typedOn(sf::Event input) {
	if (is_selected) {
		int charTyped = input.text.unicode;
		if (charTyped < 128) {
			if (hasLimit) {
				if (text.str().length() <= limit) {
					inputLogic(charTyped);
				}
				else if (text.str().length() > limit && charTyped == DELETE_KEY) {
					deleteLastChar();
				}
			}
			else {
				inputLogic(charTyped);
			}

		}
	}
}


void Textbox::inputLogic(int charTyped) {
	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
		text << static_cast<char>(charTyped);
	}
	else if (charTyped == DELETE_KEY) {
		if (text.str().length() > 0) {
			deleteLastChar();
		}

	}

	textbox.setString(text.str() + "_");

}

void Textbox::deleteLastChar() {
	std::string t = text.str();
	std::string newT = "";
	for (int i = 0; i < t.length() - 1; i++) {
		newT += t[i];
	}
	text.str("");
	text << newT;

	textbox.setString(text.str());
}



// Check if the mouse is within the bounds of the button:
bool Textbox::isMouseOver(sf::RenderWindow& window) {
	sf::Vector2i mouseCoords({ sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y });

	sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

	float mouseX = realCoords.x;
	float mouseY = realCoords.y;

	int btnPosX = positionX;
	int btnPosY = positionY;

	int btnxPosWidth = btnPosX + 250;
	int btnyPosHeight = btnPosY + textbox.getCharacterSize() + 10;

	if (mouseX < btnxPosWidth + 20 && mouseX > btnPosX - 20 && mouseY < btnyPosHeight + 20 && mouseY > btnPosY - 20) {
		return true;
	}
	return false;
}