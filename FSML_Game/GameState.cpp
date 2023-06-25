#include "GameState.h"
#include <string>
#include <fstream>

void GameState::processEvents() {
	if (showScore == true)
		displayAllHighestScores();
	if (wind.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::Closed:
			ExitGame();
			wind.close();
			break;
		case sf::Event::KeyPressed:
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code >= sf::Keyboard::Enter) {
					Run();
				}
				else if (event.key.code >= sf::Keyboard::Escape) {
					ExitGame();
					wind.close();
				}
				else if (event.key.code >= sf::Keyboard::O || showScore == true) {
					showScore = true;
					displayAllHighestScores();
				}
			}
		}
	}
}

void GameState::RenderScreen() {
	if (showScore)
		return;
	SetBGScreen();
	SetTitleScreen();
	SetStartGame();	
	SetHowToPlay();
	SetExitText();
	SetLOGOScreen();
	displayHighestScore();
	wind.display();
}

void GameState::SetBGScreen() {
	this->Background.loadFromFile("Hbg.jpg");
	bg.setTexture(Background);
	bg.scale(1, 1);

	wind.draw(bg);
}

void GameState::SetLOGOScreen() {
	this->Logo.loadFromFile("./toy-train-png.png");
	lo.setPosition(250, 100);
	lo.setTexture(Logo);
	sf::Vector2<float> scale = lo.getScale();
	if (scale.x != 0.5)
		lo.scale(0.5, 0.5);
	scale = lo.getScale();
	wind.draw(lo);
}
void GameState::SetTitleScreen() {
	font.loadFromFile("./Roboto-Bold.ttf");
	// GameTitle Train In The Desert
	GameTitle.setString(sf::String("Train In The Desert"));
	GameTitle.setFont(font);
	GameTitle.setFillColor(sf::Color::White);
	GameTitle.setCharacterSize(40);
	GameTitle.setStyle(sf::Text::Bold);
	GameTitle.setPosition(sf::Vector2f(200, 250));
	wind.draw(GameTitle);
}

void GameState::SetStartGame() {
	// StartGame message Please press Enter key To start Playing
	font.loadFromFile("./Roboto-Bold.ttf");
	StartGame.setString(sf::String("Please press Enter key To start Playing  "));
	StartGame.setFont(font);
	StartGame.setFillColor(sf::Color::White);
	StartGame.setPosition(sf::Vector2f(200, 300));
	StartGame.setOutlineThickness(1);
	StartGame.setOutlineColor(sf::Color(0,0,0,128));
	StartGame.setCharacterSize(22);
	StartGame.setStyle(sf::Text::Regular);
	wind.draw(StartGame);
}
void GameState::SetHowToPlay() {
	// HowToPlay
	font.loadFromFile("./Roboto-Bold.ttf");
	HowToPlay.setString(sf::String("How To Play :\nDirection Up    : W Or Up key\nDirection Down  : S Or Down key\nDirection Right : D Or Right key\nDirection Left  : A Or Left key"));
	HowToPlay.setFont(font);
	HowToPlay.setFillColor(sf::Color::White);
	HowToPlay.setPosition(sf::Vector2f(320, 350));
	HowToPlay.setCharacterSize(15);
	HowToPlay.setStyle(sf::Text::Regular);
	wind.draw(HowToPlay);
}

void GameState::SetExitText() {
	// ExitText
	font.loadFromFile("./Roboto-Bold.ttf");
	ExitText.setString(sf::String("To Exit :\n Press  : Esc key"));
	ExitText.setFont(font);
	ExitText.setFillColor(sf::Color::Red);
	ExitText.setPosition(sf::Vector2f(320, 480));
	ExitText.setCharacterSize(15);
	ExitText.setStyle(sf::Text::Regular);
	wind.draw(ExitText);
}

void GameState::displayHighestScore() {
	int h = highestScore();
	font.loadFromFile("./Roboto-Bold.ttf");
	HighScoreHome.setString(sf::String("Hight Score " + std::to_string(h)));
	HighScoreHome.setFont(font);
	HighScoreHome.setFillColor(sf::Color::White);
	HighScoreHome.setPosition(sf::Vector2f(520, 50));
	HighScoreHome.setCharacterSize(15);
	HighScoreHome.setStyle(sf::Text::Regular);
}
void GameState::displayAllHighestScores() {
	wind.clear();
	SetBGScreen();
	SetLOGOScreen();
	sf::Text scores;
	int* scoresArr = getScores();
	std::string* scoresNameArr = getNames();
	sf::String stringScore;
	if (NumberOfScores > 10)
	{
		for (int i = NumberOfScores - 11; i < NumberOfScores; i++)
		{
			stringScore += scoresNameArr[i] + ": " + std::to_string(scoresArr[i]) + ",\n ";
		}
	}
	else {
		for (int i = 0; i < NumberOfScores; i++)
		{
			stringScore += scoresNameArr[i] + ": " + std::to_string(scoresArr[i]) + ",\n ";
		}
	}
	scores.setString("Scores: \n" + stringScore);
	font.loadFromFile("./Roboto-Bold.ttf");
	scores.setFont(font);
	scores.setFillColor(sf::Color::White);
	scores.setPosition(sf::Vector2f(320, 250));
	scores.setCharacterSize(15);
	scores.setStyle(sf::Text::Regular);
	wind.draw(scores);
	wind.display();
}
template <class _Type>
void exapndArray(_Type*& oldArr, int& size)
{
	if (oldArr == nullptr || size == 0 || size == -1)
	{
		size++;
		_Type* newArray = new _Type[size];
		oldArr = newArray;
		return;
	}
	size++;
	_Type* newArray = new _Type[size];
	for (int i = 0; i < size - 1; i++)
	{
		newArray[i] = oldArr[i];
	}
	delete[] oldArr;
	oldArr = newArray;
}

int* GameState::getScores()
{
	std::fstream handle("score.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	std::string buffer;
	NumberOfScores = 0;
	int index = 0;
	int* scores = NULL;
	while (std::getline(handle, buffer, ';'))
	{
		buffer = (buffer[0] == '\n') ? std::string(buffer.begin() + 1, buffer.end()) : buffer;
		if (buffer.empty())
		{
			break;
		}
		std::getline(handle, buffer, ';');
		exapndArray(scores, NumberOfScores);
		scores[index] = std::stoi(buffer);
		index++;
	}
	handle.close();
	return scores;
}

std::string* GameState::getNames()
{
	std::fstream handle("score.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	std::string buffer;
	NumberOfScores = 0;
	int index = 0;
	std::string* names = NULL;
	while (std::getline(handle, buffer, ';'))
	{
		buffer = (buffer[0] == '\n') ? std::string(buffer.begin() + 1, buffer.end()) : buffer;
		if (buffer.empty())
		{
			break;
		}
		exapndArray(names, NumberOfScores);
		if (buffer.length() < 10)
		{
			for (int i = buffer.length(); i < 9; i++)
			{
				buffer += " ";
			}
		}
		names[index] = buffer;
		index++;
		std::getline(handle, buffer, ';');
	}
	handle.close();
	return names;
}
