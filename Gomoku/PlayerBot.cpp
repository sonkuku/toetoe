#include "PlayerBot.h"

#include"DEFINE.h"
#include"Draw.h"


PlayerBot::PlayerBot(int indexPlayer, std::string namePlayer, int** arrBoard, int sizeBoard, int* blankSquare, int modePlay) :
	Player(indexPlayer, namePlayer, arrBoard, sizeBoard), blankSquare(blankSquare), modePlay(modePlay)
{
    heuristic = new Heuristic();
    heuristic->setSize(sizeBoard);
    heuristic->setBoard();
    if (modePlay == BOTEASY)
    {
        heuristic->setEasy(true);
    }
    else
    {
        heuristic->setEasy(false);
    }  
}

PlayerBot::~PlayerBot()
{
    if (heuristic != nullptr)
    {
        delete heuristic;
    }
}

std::pair<int, int> PlayerBot::turn(int lastMoveX, int lastMoveY) {
    heuristic->setHumanMove(lastMoveX, lastMoveY);
    std::pair<int, int> XY = heuristic->makeMove();
    return XY;
}

