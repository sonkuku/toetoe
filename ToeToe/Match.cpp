#include "Match.h"
#include<iostream>
#include <utility>

#include "Draw.h"
#include "DEFINE.h"



Match::Match(std::string namePlayer1, std::string namePlayer2, int modePlay)
{
	this->blankSquare = new int(BOARD_SIZE * BOARD_SIZE);
	this->arrBoard = new int*[BOARD_SIZE];
	for (int row = 0; row < BOARD_SIZE; ++row)
	{
		this->arrBoard[row] = new int[BOARD_SIZE];
		for (int col = 0; col < BOARD_SIZE; ++col)
		{
			this->arrBoard[row][col] = NO_PLAYER;
		}
	}

	this->player1 = new Player(PLAYER_1, namePlayer1, arrBoard, BOARD_SIZE);
	switch (modePlay)
	{
	case OTHERPLAYER:	
		this->player2 = new Player(PLAYER_2, namePlayer2, arrBoard, BOARD_SIZE);
		break;
	default:
		this->player2 = new PlayerBot(PLAYER_2, namePlayer2, arrBoard, BOARD_SIZE, blankSquare, modePlay);
		break;
	}
	if (modePlay == BOTHARD)
	{
		this->botMoveFirst = true;
	}

	record = new RecordAndReplay::Record(BOARD_SIZE, modePlay, namePlayer1, namePlayer2);
	recordPlayer = new RecordPlayer();
}

Match::~Match()
{
	if (this->player1 != nullptr) {
		delete this->player1;
	}
	if (this->player2 != nullptr) {
		delete this->player2;
	}
	if (this->arrBoard != nullptr) {
		for (int row = 0; row < BOARD_SIZE; ++row) {
			if (this->arrBoard[row] != nullptr) {
				delete this->arrBoard[row];
			}
		}
		delete this->arrBoard;
	}
	if (this->blankSquare != nullptr)
	{
		delete this->blankSquare;
	}
	if (this->record != nullptr) 
	{
		delete record;
	}
	if (this->recordPlayer != nullptr)
	{
		delete recordPlayer;
	}

}

void Match::start()
{
	int winer;
	Draw::setNamePlayer(this->player1->getName(), this->player2->getName());
	Draw::drawBoard(BOARD_SIZE);

	if (this->botMoveFirst)
	{
		std::pair<int, int> XY;

		XY = player2->turn(-1, -1);
		this->arrBoard[XY.second][XY.first] = PLAYER_2;
		Draw::insertO(XY.first, XY.second);
		record->saveXY(XY.first, XY.second);
	}
	while (true) 
	{
		std::pair<int, int> XY(-1,-1);

		XY = player1->turn(XY.first, XY.second);
		Draw::gotoCurrentCursorAndClearLine();
		this->arrBoard[XY.second][XY.first] = PLAYER_1;
		Draw::insertX(XY.first, XY.second);
		winer = checkWin(XY.first, XY.second);
		record->saveXY(XY.first, XY.second);
		if (winer != GAME_CONTINUE) {
			break;
		}

		XY = player2->turn(XY.first, XY.second);
		Draw::gotoCurrentCursorAndClearLine();
		this->arrBoard[XY.second][XY.first] = PLAYER_2;
		Draw::insertO(XY.first, XY.second);
		winer = checkWin(XY.first, XY.second);
		record->saveXY(XY.first, XY.second);
		if (winer != GAME_CONTINUE) {
			break;
		}
	}
	if (winer == GAME_DRAW) {
		std::cout << "Game is draw!" << std::endl;
	}
	else if (winer == PLAYER_1) {
		std::cout << "Player " << player1->getName() << " win!" << std::endl;
	}
	else if (winer == PLAYER_2) {
		std::cout << "Player " << player2->getName() << " win!" << std::endl;
	}
	record->savePlayerWin(winer);
	record->writeFile();
	recordPlayer->writeFile(player1->getName(), player2->getName(), winer);
}


int Match::checkWin(int X, int Y)
{
	int nextX, nextY;
	int valuePlayer = arrBoard[Y][X];
	for (int dir = 0; dir < 4; ++dir) {
		int countSquare = 1;
		for (int range = 1; range < WIN_SCORE; ++range) {
			nextY = Y + direction[dir][0] * range;
			nextX = X + direction[dir][1] * range;
			if (nextX < 0 || nextY < 0 || nextX >= BOARD_SIZE || nextY >= BOARD_SIZE) {
				break;
			}
			if (arrBoard[nextY][nextX] == valuePlayer) {
				++countSquare;
				if (countSquare >= WIN_SCORE) {
					return valuePlayer;
				}
			}
			else {
				break;
			}
		}
		for (int range = 1; range < WIN_SCORE; ++range) {
			nextY = Y + direction[dir + 4][0] * range;
			nextX = X + direction[dir + 4][1] * range;
			if (nextX < 0 || nextY < 0 || nextX >= BOARD_SIZE || nextY >= BOARD_SIZE) {
				break;
			}
			if (arrBoard[nextY][nextX] == valuePlayer) {
				++countSquare;
				if (countSquare >= WIN_SCORE) {
					return valuePlayer;
				}
			}
			else {
				break;
			}
		}
		if (countSquare >= WIN_SCORE) {
			return valuePlayer;
		}
	}

	if (--(*(this->blankSquare)) == GAME_DRAW) {
		return GAME_DRAW;
	}
	return GAME_CONTINUE; // no player win
}
