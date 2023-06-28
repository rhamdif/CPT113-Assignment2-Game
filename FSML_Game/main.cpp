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

	sf::Texture BackgroundHome;
	sf::Sprite bgH;
	sf::Texture LogoH;
	sf::Sprite loH;

	LogoH.loadFromFile("./toy-train-png.png");
	loH.setPosition(320, 80);
	loH.setTexture(LogoH);
	sf::Vector2<float> scale = loH.getScale();
	if (scale.x != 0.5)
		loH.scale(0.4, 0.4);
	scale = loH.getScale();

	BackgroundHome.loadFromFile("Hbg.jpg");
	bgH.setTexture(BackgroundHome);
	bgH.scale(1, 1);


	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
	window.create(sf::VideoMode(800, 600), "Train Game", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);
	sf::Font font;
	font.loadFromFile("Roboto-Bold.ttf");

	Textbox textbox1(320, 320, 20, sf::Color::White, false);
	textbox1.setLabel(std::string("FristPlayer name:"), sf::Color::White, 18);

	Textbox textbox2(320, 400, 20, sf::Color::White, false);
	textbox2.setLabel(std::string("Second Player name:"), sf::Color::White, 18);

	// One Player button:
	Button btnOnePlayer("One Player", { 200, 50 }, 17, sf::Color::Green, sf::Color::Black);
	btnOnePlayer.setFont(font);
	btnOnePlayer.setPosition(sf::Vector2f(230, 200));
	// Tow Player button:
	Button btnTowPlayer("Tow Players", { 200, 50 }, 17, sf::Color::Green, sf::Color::Black);
	btnTowPlayer.setFont(font);
	btnTowPlayer.setPosition(sf::Vector2f(450, 200));

	// Start Game Button:
	Button btnStartGame("Start Game", { 150, 50 }, 17, sf::Color::Green, sf::Color::Black);
	btnStartGame.setFont(font);
	btnStartGame.setPosition(sf::Vector2f(280, 500));

	// Exit Game Button:
	Button btnExitGame("Exit", { 150, 50 }, 17, sf::Color::Red, sf::Color::White);
	btnExitGame.setFont(font);
	btnExitGame.setPosition(sf::Vector2f(480, 500));



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
				if (btnExitGame.isMouseOver(window)) {
					// Highlight buttons when mouse is over them:
					btnExitGame.setBackColor(sf::Color(255, 0, 0));
				}
				else {
					btnExitGame.setBackColor(sf::Color(169, 10, 10));
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
				}
				if (btnTowPlayer.isMouseOver(window)) {
					players = 2;
				}
				if (btnExitGame.isMouseOver(window)) {
					window.close();
				}
				// start Game
				if (btnStartGame.isMouseOver(window)) {
					if (players == 1 && textbox1.getText().length()> 0) {
						GameState gameS(textbox1.getText());
					}
					else if (players == 2 && textbox1.getText().length() > 0 && textbox2.getText().length() > 0) {
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
			window.draw(bgH);
			textbox1.drawTo(window);
			
		}
		else if(players == 2) {
			window.clear();
			window.draw(bgH);
			textbox1.drawTo(window);
			textbox2.drawTo(window);
		}
		
			
	
		window.draw(loH);
		btnOnePlayer.drawTo(window);
		btnTowPlayer.drawTo(window);
		btnStartGame.drawTo(window);
		btnExitGame.drawTo(window);
	

		window.display();
	}
		
		

	return 0;
}