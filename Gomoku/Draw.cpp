#include "Draw.h"
#include <iostream>
#include <windows.h>

#include"DEFINE.h"


HANDLE Draw::hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO Draw::ScreenBufferInfo = {0};
std::string Draw::namePlayer1, Draw::namePlayer2;
int Draw::sizeBoard;

void Draw::insertSpace(int space)
{
    for (int i = 0; i < space; ++i) {
        std::cout << " ";
    }
}

void Draw::gotoXY(int x, int y)
{
    COORD Cord;
    Cord.X = x;
    Cord.Y = y;
    SetConsoleCursorPosition(Draw::hStdout, Cord);
}


void Draw::setNamePlayer(std::string namePlayer1, std::string namePlayer2)
{
    Draw::namePlayer1 = namePlayer1;
    Draw::namePlayer2 = namePlayer2;
}

void Draw::drawBoard(int sizes)
{
    Draw::sizeBoard = sizes;
    insertSpace(5);
    std::cout << namePlayer1 << " = X, " << namePlayer2 << " = O " << std::endl;
    insertSpace(5);
    for (int col = 0; col < sizes; ++col) {
        std::cout << "  " << col << " ";
    }
    std::cout << std::endl;
    insertSpace(5);
    for (int col = 0; col <= sizes * 4; ++col) {

        if (col % 4 == 0) {
            std::cout << "|";
        }
        else {
            std::cout << "-";
        }
    }
    std::cout << std::endl;
    for (int row = 0; row < sizes; ++row) {
        insertSpace(2);
        std::cout << row;
        insertSpace(2);
        for (int col = 0; col < sizes; ++col) {
            std::cout << "|   ";
        }
        std::cout << "|" << std::endl;
        insertSpace(5);
        for (int col = 0; col < sizes; ++col) {
            std::cout << "|---";
        }
        std::cout << "|" << std::endl;
    }
    GetConsoleScreenBufferInfo(Draw::hStdout, &ScreenBufferInfo);
}

void Draw::insertX(int x, int y)
{
    if (y < sizeBoard && x < sizeBoard && x >= 0 && y >= 0) {
        gotoXY(7 + x * 4, 3 + 2 * y);
        std::cout << GREEN << "X" << RESET << std::endl;
    }
    gotoCurrentCursorAndClearLine();
}

void Draw::insertO(int x, int y)
{
    if (y < sizeBoard && x < sizeBoard && x >= 0 && y >= 0) {
        gotoXY(7 + x * 4, 3 + 2 * y);
        std::cout << RED << "O" << RESET << std::endl;
    } 
    gotoCurrentCursorAndClearLine();
}

void Draw::gotoCurrentCursorAndClearLine()
{
    CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfoTemp;
    GetConsoleScreenBufferInfo(Draw::hStdout, &ScreenBufferInfoTemp);

    for (int i = ScreenBufferInfoTemp.dwCursorPosition.Y; i >= ScreenBufferInfo.dwCursorPosition.Y; --i)
    {
        gotoXY(ScreenBufferInfo.dwCursorPosition.X, i);
        insertSpace(80);
    }
    gotoXY(ScreenBufferInfo.dwCursorPosition.X, ScreenBufferInfo.dwCursorPosition.Y);
}
