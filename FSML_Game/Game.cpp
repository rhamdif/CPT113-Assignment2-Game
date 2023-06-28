#include "Game.h"
#include <fstream>
#define side 15
#define size 208.5

NODE Game::insertHead(NODE head, sf::Sprite* sprite) {
	NODE temp;
	temp = (NODE)malloc(sizeof(struct node));
	switch (head->direction) {
	case direction(up):
		temp->posy = head->posy - side * 2;
		temp->posx = head->posx; break;
	case direction(down):
		temp->posy = head->posy + side * 2;
		temp->posx = head->posx; break;
	case direction::left:
		temp->posx = head->posx - side * 2;
		temp->posy = head->posy; break;
	case direction::right:
		temp->posx = head->posx + side * 2;
		temp->posy = head->posy; break;
	}
	temp->direction = head->direction;
	temp->s = sprite;
	temp->llink = NULL;
	temp->rlink = head;
	head->llink = temp;
	return temp;
}

NODE Game::deleteTail(NODE tail) {
	NODE temp;
	temp = tail->llink;
	temp->rlink = NULL;
	free(tail);
	tail = NULL;
	return temp;
}
void Game::Update2()
{
	if (head2->posx > 810)
		head2->posx = 0;
	if (head2->posx < 0)
		head2->posx = 810;
	if (head2->posy > 600)
		head2->posy = 0;
	if (head2->posy < 0)
		head2->posy = 600;
	head2 = insertHead(head2, &TrainSprite2);
	tail2 = deleteTail(tail2);
	HandleSnoopyTouched2();
	checkInterSection2(head2, &window);
	count2 = 0;

}

void Game::Update() {
	
	if (head1->posx > 810)
		head1->posx = 0;
	if (head1->posx < 0)
		head1->posx = 810;
	if (head1->posy > 600)
		head1->posy = 0;
	if (head1->posy < 0)
		head1->posy = 600;	
	head1 = insertHead(head1, &TrainSprite);
	tail1 = deleteTail(tail1);	
	HandleSnoopyTouched();
	checkInterSection1(head1, &window);
	count = 0;


}

void Game::Start() {
	LoadSprites();

	head1 = (NODE)malloc(sizeof(struct node));
	head1->posx = 150;
	head1->posy = 150;
	head1->direction = right;
	head1->s = &TrainSprite;
	head1->llink = head1->rlink = NULL;
	tail1 = head1;
	if (playersCount > 1)
	{
		head2 = (NODE)malloc(sizeof(struct node));
		head2->posx = 100;
		head2->posy = 100;
		head2->direction = right;
		head2->s = &TrainSprite2;
		head2->llink = head2->rlink = NULL;
		tail2 = head2;
	}
	sf::Vector2f INIT_COORDS = getSnoopyCoords();
	snoopy.setPosition(0, 0);
	Score.setPosition(550, 10);
	Score2.setPosition(550, 50);
	window.create(sf::VideoMode(800, 600), "Train", sf::Style::Titlebar | sf::Style::Close);
}



void Game::Run() {
	Start();
	while (window.isOpen()) {
		Render();
		processEvents();
		setSpeed(playingLevel);
		if (count == speed) {
			Update();
		}
		if (playersCount > 1)
		{
			if (count2 == speed2) {
				Update2();
			}
		}
		count2++;
		count++;
	}
}
void Game::Render() {
	window.clear();
	window.draw(bg);
	window.draw(Score);
	window.draw(Score2);
	cur1 = head1;
	cur2 = head2;
	setHeadSprite(head1, &TrainSprite); 
	if (playersCount > 1)
		setHeadSprite(head2, &TrainSprite2);
	if (!PauseGame) {
		while (cur1 != NULL) {
			if (cur1 != head1)
				setTrailingSprite(cur1, &TrainSprite);
			(*cur1->s).setPosition(cur1->posx, cur1->posy);
			window.draw(*cur1->s);
			cur1 = cur1->rlink;
		}
		if (playersCount > 1)
		{
			while (cur2 != NULL)
			{
				if (cur2 != head2)
					setTrailingSprite(cur2, &TrainSprite2);
				(*cur2->s).setPosition(cur2->posx, cur2->posy);
				window.draw(*cur2->s);
				cur2 = cur2->rlink;
			}
		}
	
		window.draw(snoopy);
		window.display();
	}
	else {
		PauseGameState();
		window.display();
	}
	
}

void Game::LoadSprites() {
	this->spriteSheet.loadFromFile("./trainsprite.png");
	TrainSprite.setTexture(spriteSheet);
	TrainSprite.setScale(sf::Vector2f(0.25, 0.25));
	TrainSprite.setOrigin(104.5, 104.5);

	this->spriteSheet2.loadFromFile("./trainsprite2.png");
	TrainSprite2.setTexture(spriteSheet2);
	TrainSprite2.setScale(sf::Vector2f(0.25, 0.25));
	TrainSprite2.setOrigin(104.5, 104.5);


	snoopy.setTexture(spriteSheet);
	snoopy.setTextureRect(sf::IntRect(size * 3, size * 1, size, size));
	snoopy.setScale(0.2, 0.2);
	snoopy.setOrigin(104.5, 104.5);

	font.loadFromFile("./Roboto-Bold.ttf");
	Score.setFont(font);
	Score.setFillColor(sf::Color::Black);
	Score2.setFont(font);
	Score2.setFillColor(sf::Color::Black);
	this->Background.loadFromFile("./sand.jpg");
	bg.setTexture(Background);
	bg.scale(2, 2);

	// home messages
	font.loadFromFile("./Roboto-Bold.ttf");
	GameTitle.setFont(font);
	GameTitle.setFillColor(sf::Color::Black);

	StartGame.setFont(font);
	StartGame.setFillColor(sf::Color::Black);


}

void Game::setHeadSprite(NODE head, sf::Sprite* sp) {
	switch (head->direction)
	{
	case up:
		sp->setTextureRect(sf::IntRect(size * 1, size * 0, size, size));
		head->s = sp;
		break;
	case down:
		sp->setTextureRect(sf::IntRect(size * 0, size * 0, size, size));
		head->s = sp;
		break;
	case left:
		sp->setTextureRect(sf::IntRect(size * 3, size * 0, size, size));
		head->s = sp;
		break;
	case right:
		sp->setTextureRect(sf::IntRect(size * 2, size * 0, size, size));
		head->s = sp;
		break;
	}
};

void Game::setTrailingSprite(NODE node, sf::Sprite* sp) {
	switch (node->direction)
	{
	case up:
		sp->setTextureRect(sf::IntRect(size * 1, size * 1, size, size));
		node->s = sp;
		break;
	case down:
		sp->setTextureRect(sf::IntRect(size * 2, size * 1, size, size));
		node->s = sp;
		break;
	case left:
		sp->setTextureRect(sf::IntRect(size * 0, size * 1, size, size));
		node->s = sp;
		break;
	case right:
		sp->setTextureRect(sf::IntRect(size * 0, size * 1, size, size));
		node->s = sp;
		break;
	}
};

void Game::processEvents() {
	if (window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::Closed:
			ExitGame();
			window.close();
			break;
		case sf::Event::KeyPressed:
			if (PauseGame) {
				if (event.key.code == sf::Keyboard::P) {
					PauseGame = !PauseGame;
				}
				else if (event.key.code == sf::Keyboard::X) {
					ExitGame();
					window.close();
				}
			}
			else {
				if ((event.key.code == sf::Keyboard::Up) && head1->direction != down) {
					head1->direction = up;
				}
				else if ((event.key.code == sf::Keyboard::Down) && head1->direction != up) {
					head1->direction = down;
				}
				else if ((event.key.code == sf::Keyboard::Left) && head1->direction != right) {
					head1->direction = left;
				}
				else if ((event.key.code == sf::Keyboard::Right) && head1->direction != left) {
					head1->direction = right;
				}
				if (playersCount > 1)
				{
					if (event.key.code == sf::Keyboard::D && head2->direction != left)
					{
						head2->direction = right;
					}	
					else if (event.key.code == sf::Keyboard::A && head2->direction != right)
					{
						head2->direction = left;
					}				
					else if (event.key.code == sf::Keyboard::W && head2->direction != down)
					{
						head2->direction = up;
					}				
					else if (event.key.code == sf::Keyboard::S && head2->direction != up)
					{
						head2->direction = down;
					}
					else if (event.key.code == sf::Keyboard::P) {
						PauseGame = !PauseGame;
					}
				}
				
			}
		}
	}
}


sf::Vector2f Game::getSnoopyCoords() {
	return sf::Vector2f((rand() % 15 + 1) * side * 2, (rand() % 9 + 1) * side * 2);
};

void Game::HandleSnoopyTouched() {
	if (isSnoopyTouched(head1, &snoopy)) {
		head1 = insertHead(head1, &TrainSprite);
		speed--;
		while (1)
		{
			snoopyPos = getSnoopyCoords();
			cur1 = head1;
			while (cur1 != NULL) {
				if (cur1->posx == snoopyPos.x && cur1->posy == snoopyPos.y) {
					break;
				}
				cur1 = cur1->rlink;
			}
			if (cur1 == NULL)
				break;
		}
		snoopy.setPosition(getSnoopyCoords());
		score++;
		if (playersCount > 1)
		{
			Score.setString(sf::String(name + " : " + std::to_string(score)));
		}
		else {
			Score.setString(sf::String(name + " : " + std::to_string(score)));
		}
		
	}
};
void Game::HandleSnoopyTouched2() {
	if (isSnoopyTouched2(head2, &snoopy)) {
		head2 = insertHead(head2, &TrainSprite2);
		speed2--;
		while (1)
		{
			snoopyPos = getSnoopyCoords();
			cur2 = head2;
			while (cur2 != NULL) {
				if (cur2->posx == snoopyPos.x && cur2->posy == snoopyPos.y) {
					break;
				}
				cur2 = cur2->rlink;
			}
			if (cur2 == NULL)
				break;
		}
		snoopy.setPosition(getSnoopyCoords());
		score2++;
		Score2.setString(sf::String(name2 + " : " + std::to_string(score2)));
	}
};

bool Game::isSnoopyTouched2(NODE head, sf::Sprite* snoopy) {
	auto stuff = snoopy->getPosition();
	if (sf::Vector2f(head->posx, head->posy) == snoopy->getPosition())
	{
		return true;
	}
	else if (sf::Vector2f(head->posx - 10, head->posy - 10) == snoopy->getPosition())
	{
		return true;
	}	
	else if (sf::Vector2f(head->posx + 10, head->posy + 10) == snoopy->getPosition())
	{
		return true;
	}	
	else if (sf::Vector2f(head->posx - 10, head->posy + 10) == snoopy->getPosition())
	{
		return true;
	}	
	else if (sf::Vector2f(head->posx + 10, head->posy - 10) == snoopy->getPosition())
	{
		return true;
	}	
	else if (sf::Vector2f(head->posx, head->posy - 10) == snoopy->getPosition())
	{
		return true;
	}	
	else if (sf::Vector2f(head->posx, head->posy + 10) == snoopy->getPosition())
	{
		return true;
	}	
	else if (sf::Vector2f(head->posx +10, head->posy) == snoopy->getPosition())
	{
		return true;
	}	
	else if (sf::Vector2f(head->posx -10, head->posy) == snoopy->getPosition())
	{
		return true;
	}
	return false;
}
bool Game::isSnoopyTouched(NODE head, sf::Sprite* snoopy) {
	return sf::Vector2f(head->posx, head->posy) == snoopy->getPosition();
}
void Game::checkInterSection1(NODE head, sf::RenderWindow* window) {
	NODE cur = head->rlink;
	while (cur != NULL) {
		if (head->posx == cur->posx && head->posy == cur->posy) {
			FileStoreScore(score);
			score = 0;
			if (playersCount > 1)
			{
				Score.setString(sf::String(name + " : " + std::to_string(score)));
			}
			else {
				Score.setString(sf::String(name + " : " + std::to_string(score)));
			}
			Score2.setString(sf::String(name2 + " : " + std::to_string(score2)));
			window->close();
		}
		cur = cur->rlink;
	}
};

void Game::checkInterSection2(NODE head, sf::RenderWindow* window) {
	NODE cur = head->rlink;
	while (cur != NULL) {
		if (head->posx == cur->posx && head->posy == cur->posy) {
			FileStoreScore(score);
			score2 = 0;
			if (playersCount > 1)
			{
				Score.setString(sf::String(name + " : " + std::to_string(score)));
			}
			else {
				Score.setString(sf::String(name + " : " + std::to_string(score)));
			}
			Score2.setString(sf::String(name2 + " : " + std::to_string(score2)));
			window->close();
		}
		cur = cur->rlink;
	}
};


void Game::PauseGameState() {
	// background for Pause State;
	PauseBackground.setSize(sf::Vector2f(400, 150));
	PauseBackground.setFillColor(sf::Color(0, 0, 0, 128));
	PauseBackground.setPosition(200, 200);
	// text Pause state Message;
	font.loadFromFile("./Roboto-Bold.ttf");
	PauseTitle.setString("Press [ P ] to continue Playing");
	PauseTitle.setPosition(230, 250);
	PauseTitle.setCharacterSize(25);
	PauseTitle.setFont(font);
	PauseTitle.setFillColor(sf::Color::White);
	// text Exit Game;
	ExitTitle.setString("Press [ X ] to Exit");
	ExitTitle.setPosition(320, 290);
	ExitTitle.setCharacterSize(15);
	ExitTitle.setFont(font);
	ExitTitle.setFillColor(sf::Color::White);


	window.draw(PauseBackground);
	window.draw(PauseTitle);
	window.draw(ExitTitle);

}

void Game::FileStoreScore(int score) {
	std::ofstream MyFile;
	MyFile.open("score.txt", std::fstream::app);
	if (playersCount == 1) {
		MyFile << name << ";" << score << ";\n";
	}
	else if (playersCount == 2) {
		MyFile << name << ";" << score << ";\n";
		MyFile << name2 << ";" << score2 << ";\n";
	}
	
	MyFile.close();
}

void Game::ExitGame() {
	FileStoreScore(score);
	score = 0;
	score2 = 0;
	if (playersCount > 1)
	{
		Score.setString(sf::String(name+ " : " + std::to_string(score)));
	}
	else {
		Score.setString(sf::String(name + " : " + std::to_string(score)));
	}
	Score2.setString(sf::String(name2 + " : " + std::to_string(score2)));
	window.close();
}