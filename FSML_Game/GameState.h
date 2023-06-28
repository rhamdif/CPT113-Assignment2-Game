#pragma once
#include "Game.h"
class GameState : public Game
{
private:
	bool showScore = false;
	int NumberOfScores = 0;
	std::string name;
	std::string name2;
	bool GameStatus = false;
	int HighScore = 0;
	sf::RenderWindow wind;
	sf::RenderWindow ScoresWind;
	sf::Texture Background;
	sf::Sprite bg;
	sf::Text GameTitle;
	sf::Text StartGame;
	sf::Font font;
	sf::Event event;
	sf::Texture Logo;
	sf::Sprite lo;
	sf::Text HowToPlay;
	sf::Text ExitText;
	sf::Text HighScoreHome;
	sf::String playerName;
	sf::Text playerTextName;
	sf::String playerInput;
	sf::Text playerText;
	void processEvents();
	void RenderScreen();
	
	void SetLOGOScreen();
	void SetTitleScreen();
	void SetStartGame();
	void SetHowToPlay();
	void SetExitText();
	void FileStoreScore(int score);
	int* getScores();
	std::string* getNames();
	void displayHighestScore();
	void displayAllHighestScores();
	int highestScore()
	{
		int* scores = getScores();
		if (scores != NULL)
		{
			std::sort(scores, scores + NumberOfScores);
			return scores[NumberOfScores-1];
		}
		else
			return -1;
	}
public:
	void SetBGScreen();
	template <class _Type>
	friend void exapndArray (_Type*& oldArr, int& size);
	GameState(std::string name, int playingLevel) : name(name), Game(name)
	{
		GameStatus = false;
		Game::setSpeed(playingLevel);
		wind.create(sf::VideoMode(800, 600), "Start", sf::Style::Titlebar | sf::Style::Close);
		while (wind.isOpen()) {
			RenderScreen();
			processEvents();
		}

	}	
	GameState(std::string name, std::string name2, int playingLevel) : name(name), name2(name2), Game(name, name2)
	{
		GameStatus = false;
		wind.create(sf::VideoMode(800, 600), "Start", sf::Style::Titlebar | sf::Style::Close);
		while (wind.isOpen()) {
			RenderScreen();
			processEvents();
		}

	}
};


