#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
struct node {
	int posx, posy;
	int direction;
	sf::Sprite* s;
	struct node* llink;
	struct node* rlink;
};

typedef struct node* NODE;

enum direction {
	up, down, left, right
};

class Game
{
private:
	NODE head1, tail1, cur1;
	NODE head2, tail2, cur2;
	int speed = 600;
	int speed2 = 600;
	int count = 0;
	int count2 = 0;
	int score = 0;
	int score2 = 0;
	int playersCount = 1;
	std::string name;
	std::string name2;
	bool nameExists = false;
	bool PauseGame = false;
private:
	sf::RenderWindow window;
	sf::Sprite TrainSprite;
	sf::Sprite TrainSprite2;
	sf::Texture spriteSheet;
	sf::Sprite snoopy;
	sf::Event event;
	sf::Vector2f snoopyPos;
	sf::Text Score;
	sf::Text Score2;
	sf::Text GameTitle;
	sf::Text StartGame;
	sf::Font font;
	sf::Texture Background;
	sf::Sprite bg;
	sf::RectangleShape PauseBackground;
	sf::Text PauseTitle;
	sf::Text ExitTitle;
	void Update();
	void Update2();
	void Render();
	void Start();
	
	NODE insertHead(NODE head, sf::Sprite* sprite);
	NODE deleteTail(NODE tail);
	void processEvents();
	void PauseGameState();
	void FileStoreScore(int score);
private:
	void setTrailingSprite(NODE node, sf::Sprite* sp);
	void setHeadSprite(NODE head, sf::Sprite* sp);
	sf::Vector2f getSnoopyCoords();
	void HandleSnoopyTouched();
	void HandleSnoopyTouched2();
	bool isSnoopyTouched(NODE head, sf::Sprite* snoopy);
	bool isSnoopyTouched2(NODE head, sf::Sprite* snoopy);
	void checkInterSection(NODE head, sf::RenderWindow* window);
public:
	
	Game(std::string name) : name(name), playersCount(1) {}
	Game(std::string name, std::string n2) : name(name),name2(n2), playersCount(2) {}
	Game() = delete; // disable default constructor
	void Run();
	void LoadSprites();
	void ExitGame();
};

