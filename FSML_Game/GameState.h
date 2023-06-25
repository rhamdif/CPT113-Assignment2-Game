#pragma once
#include "Game.h"
class GameState : public Game
{
private:
	bool showScore = false;
	int NumberOfScores = 0;
	std::string name;
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
	void processEvents();
	void RenderScreen();
	void SetBGScreen();
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
	template <class _Type>
	friend void exapndArray
	(_Type*& oldArr, int& size);
	GameState(std::string name) : name(name), Game(name)
	{
		GameStatus = false;
		wind.create(sf::VideoMode(800, 600), "Start", sf::Style::Titlebar | sf::Style::Close);
		while (wind.isOpen()) {
			RenderScreen();
			processEvents();
		}

	}
};


