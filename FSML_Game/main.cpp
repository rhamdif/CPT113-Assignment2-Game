#include "Game.h"
#include "GameState.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Textbox.h"
#include "Button.h"

using namespace std;

int main() {
	int players = 1;
	bool HTP = false;
	/*
	std::cout << "Enter your name: ";
	std::string name;
	std::cin >> name;
	if (name.length() > 10)
	{
		std::cout << "NAME LENGTH MUST NOT BE OVER 10 CHARACTERS LONG ";
		system("pause");
		exit(-10);
	}
	for (int i = 0; i < name.length(); i++)
	{
		if (name[i] == ';')
		{
			std::cout << "CHARACTER ; NOT ALLOWED IN THE NAME";
			system("pause");
			exit(-1);
		}
	}
	GameState gameS(name);

	*/

	sf::Text HowToPlay;
	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
	window.create(sf::VideoMode(900, 900), "Train Game", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);
	sf::Font font;
	font.loadFromFile("Roboto-Bold.ttf");

	Textbox textbox1(380, 320, 20, sf::Color::White, false);
	textbox1.setLabel(std::string("FristPlayer name:"), sf::Color::White, 18);

	Textbox textbox2(380, 420, 20, sf::Color::White, false);
	textbox2.setLabel(std::string("Second Player name:"), sf::Color::White, 18);

	// One Player button:
	Button btnOnePlayer("One Player", { 200, 50 }, 17, sf::Color::Green, sf::Color::Black);
	btnOnePlayer.setFont(font);
	btnOnePlayer.setPosition(sf::Vector2f(170, 200));
	// Tow Player button:
	Button btnTowPlayer("Tow Players", { 200, 50 }, 17, sf::Color::Green, sf::Color::Black);
	btnTowPlayer.setFont(font);
	btnTowPlayer.setPosition(sf::Vector2f(400, 200));

	// Start Game Button:
	Button btnStartGame("Start Game", { 200, 50 }, 17, sf::Color::Green, sf::Color::Black);
	btnStartGame.setFont(font);
	btnStartGame.setPosition(sf::Vector2f(380, 500));

	// How to Play
	Button howToPlay("How To Play?", { 170, 50 }, 17, sf::Color(200,100,100), sf::Color::White);
	howToPlay.setFont(font);
	howToPlay.setPosition(sf::Vector2f(630, 200));

	// while to check events on window is open
	while (window.isOpen()) {
		sf::Event Event;
		while (window.pollEvent(Event)) {
			switch (Event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:
				textbox1.typedOn(Event);
				textbox2.typedOn(Event);
				break;
			case sf::Event::MouseMoved:
				// Main menu:
				if (btnOnePlayer.isMouseOver(window)) {
					// Highlight buttons when mouse is over them:
					btnOnePlayer.setBackColor(sf::Color(153, 204, 0));
				}
				else {
					btnOnePlayer.setBackColor(sf::Color(102, 102, 51));
				}
				if (btnTowPlayer.isMouseOver(window)) {
					// Highlight buttons when mouse is over them:
					btnTowPlayer.setBackColor(sf::Color(153, 204, 0));
				}
				else {
					btnTowPlayer.setBackColor(sf::Color(102, 102, 51));
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (textbox1.isMouseOver(window)) {
					textbox2.setSelected(false);
					textbox1.setSelected(true);
				}
				if (textbox2.isMouseOver(window)) {
					textbox1.setSelected(false);
					textbox2.setSelected(true);
				}
				// 
				if (btnOnePlayer.isMouseOver(window)) {
					players = 1;
					HTP = false;
				}
				if (btnTowPlayer.isMouseOver(window)) {
					players = 2;
					HTP = false;
				}
				if (howToPlay.isMouseOver(window)) {
					// HowToPlay
					HTP = !HTP;
					font.loadFromFile("./Roboto-Bold.ttf");
					HowToPlay.setString(sf::String("How To Play :\nDirection Up    : W Or Up key\nDirection Down  : S Or Down key\nDirection Right : D Or Right key\nDirection Left  : A Or Left key"));
					HowToPlay.setFont(font);
					HowToPlay.setFillColor(sf::Color::White);
					HowToPlay.setPosition(sf::Vector2f(380, 300));
					HowToPlay.setCharacterSize(15);
					HowToPlay.setStyle(sf::Text::Regular);
				}
				// start Game
				if (btnStartGame.isMouseOver(window)) {
					if (players == 1 && textbox1.getText().length()> 0) {
						GameState gameS(textbox1.getText());
					}
					else if (players == 2) {
						GameState gameS(textbox1.getText(), textbox2.getText());
					}
				}
							
				break;
			default:
				break;
			}
		}

		
		// Drow Buttons
		if (players == 1) {
			window.clear();
			textbox1.drawTo(window);
			
		}
		else if(players == 2) {
			window.clear();
			textbox1.drawTo(window);
			textbox2.drawTo(window);
		}
		if (HTP) {
			window.clear();
			window.draw(HowToPlay);
		}
			
		


		btnOnePlayer.drawTo(window);
		btnTowPlayer.drawTo(window);
		howToPlay.drawTo(window);
		btnStartGame.drawTo(window);

		window.display();
	}
		
		

	return 0;
}