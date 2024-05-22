#pragma once
#include<mutex>
#include<Windows.h>
#include<string>


class Draw
{
private:
	static HANDLE hStdout;
	static CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;
	static std::string namePlayer1, namePlayer2;
	static int sizeBoard;
	
	static void insertSpace(int space);	
	static void gotoXY(int x, int y); //move cursor to position x, y in console
public:
	static void setNamePlayer(std::string namePlayer1, std::string namePlayer2);
	static void drawBoard(int sizes); // print board in console
	static void insertX(int x, int y); // print X in position X, Y
	static void insertO(int x, int y); // print O in position X, Y
	static void gotoCurrentCursorAndClearLine(); // used move back cursor to position old and clear lines printed
};

