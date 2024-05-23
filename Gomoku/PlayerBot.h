#pragma once
#include "Player.h"
#include "Heuristic.h"
#include <vector>
#include <utility>

class PlayerBot : public Player
{
private:
	int* blankSquare;
	int modePlay;
	Heuristic* heuristic;
public:
	PlayerBot(int indexPlayer, std::string namePlayer, int** arrBoard, int sizeBoard, int* blankSquare, int modePlay);
	~PlayerBot();

	std::pair<int, int> turn(int lastMoveX, int lastMoveY);
};

