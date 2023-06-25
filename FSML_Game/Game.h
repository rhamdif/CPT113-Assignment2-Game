#pragma once
#include <SFML/Graphics.hpp>
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
	NODE head, tail, cur;
	int speed = 300;
	int count = 0;
	int score = 0;
	std::string name;
	bool nameExists = false;
	bool PauseGame = false;
private:
	sf::RenderWindow window;
	sf::Sprite TrainSprite;
	sf::Texture spriteSheet;
	sf::Sprite snoopy;
	sf::Event event;
	sf::Vector2f snoopyPos;
	sf::Text Score;
	sf::Text GameTitle;
	sf::Text StartGame;
	sf::Font font;
	sf::Texture Background;
	sf::Sprite bg;
	sf::RectangleShape PauseBackground;
	sf::Text PauseTitle;
	sf::Text ExitTitle;
	void Update();
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
	bool isSnoopyTouched(NODE head, sf::Sprite* snoopy);
	void checkInterSection(NODE head, sf::RenderWindow* window);
public:
	Game(std::string name) : name(name) {}
	Game() {}
	void Run();
	void LoadSprites();
	void ExitGame();
};

