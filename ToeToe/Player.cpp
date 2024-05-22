#include "Player.h"
#include<iostream>

#include"DEFINE.h"
#include "Draw.h"



Player::Player(int indexPlayer, std::string namePlayer, int** arrBoard, int sizeBoard) :
	indexPlayer(indexPlayer), name(namePlayer), arrBoard(arrBoard), sizeBoard(sizeBoard)
{
}

Player::~Player()
{
}

std::string Player::getName()
{
	return this->name;
}

std::pair<int, int> Player::turn(int lastMoveX, int lastMoveY)
{
	int X, Y;
	while (true) {
		std::cout << "Player " << this->name << "'s turn: ";
		std::cin >> Y >> X;

		// check if input are string or char
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(256, '\n');
			Draw::gotoCurrentCursorAndClearLine();
			continue;
		}
		if (X >= 0 && Y >= 0 && X < sizeBoard && Y < sizeBoard && arrBoard[Y][X] == 0) {
			break;
		}
		Draw::gotoCurrentCursorAndClearLine();
	}
	return std::pair<int, int>(X, Y);
}
