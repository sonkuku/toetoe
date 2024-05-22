#pragma once
#include"Player.h"
#include"PlayerBot.h"
#include<string>
#include"RecordAndReplay.h"
#include "RecordPlayer.h"


class Match
{
private:
	int** arrBoard;
	Player* player1,* player2;
	int* blankSquare;
	bool botMoveFirst;
	RecordAndReplay::Record* record;
	RecordPlayer* recordPlayer;

public:
	Match(std::string namePlayer1, std::string namePlayer2, int modePlay);
	~Match();

	int checkWin(int X, int Y); // check winning conditions
	void start();				// start match
};

