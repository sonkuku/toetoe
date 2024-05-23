#pragma once
#include<string>
#include<utility>

class Player
{
protected:
	std::string name;
	int sizeBoard;
	int indexPlayer;
	int** arrBoard;
public:
	Player(int indexPlayer, std::string namePlayer, int** arrBoard, int sizeBoard);
	virtual ~Player();

	std::string getName();
	virtual std::pair<int, int> turn(int lastMoveX, int lastMoveY);
};

