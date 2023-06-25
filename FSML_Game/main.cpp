#include "Game.h"
#include "GameState.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
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
	
	return 0;
}