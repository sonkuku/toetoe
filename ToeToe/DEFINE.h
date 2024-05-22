#pragma once

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"      
#define MAGENTA "\033[35m"

#define fileLogMatch "historyMath.txt"
#define fileLogScorePlayer "historyScorePlayer.txt"

#define PLAYER_1 1
#define PLAYER_2 -1
#define NO_PLAYER 0

#define GAME_DRAW 0
#define GAME_CONTINUE 99

#define BOARD_SIZE 10
#define WIN_SCORE 4

const int direction[8][2] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

const enum MODEPLAY
{
	OTHERPLAYER,
	BOTEASY,
	BOTNORMAL,
	BOTHARD
};

