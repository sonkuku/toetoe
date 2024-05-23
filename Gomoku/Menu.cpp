#include "Menu.h"
#include<iostream>
#include<string>
#include<windows.h>

#include"DEFINE.h"
#include"Match.h"
#include"RecordAndReplay.h"
#include"Draw.h"
#include"RecordPlayer.h"




void Menu::playWithOtherPlayer()
{
	std::string namePlayer1, namePlayer2;
	std::cout << "Enter Player1's name: ";
	std::getline(std::cin, namePlayer1);
	std::cout << "Enter Player2's name: ";
	std::getline(std::cin, namePlayer2);

	system("cls");
	Match* match = new Match(namePlayer1, namePlayer2, OTHERPLAYER);
	match->start();
	delete match;
	system("pause");
}

void Menu::playWithBot()
{
	std::string key;
	int keyInt;
	do
	{
		system("cls");
		std::cout << YELLOW << "*-------" << RESET << "Play with BOT" << YELLOW << "-------*" << RESET << std::endl;
		std::cout << "Press number to choise:" << std::endl;
		std::cout << MAGENTA << "1.Easy" << RESET << " Mode" << std::endl;
		std::cout << MAGENTA << "2.Normal" << RESET << " Mode" << std::endl;
		std::cout << MAGENTA << "3.Hard" << RESET << " Mode" << std::endl;
		std::cout << MAGENTA << "4.Back" << RESET << " to MAIN MENU" << std::endl;
		std::getline(std::cin, key);
	} while (key.length() != 1 || ((keyInt = int(key[0] - '0')) != BOTEASY && keyInt != BOTNORMAL && keyInt != BOTHARD && keyInt != 4) );
	if (keyInt == 4)
	{
		return;
	}

	std::string namePlayer;
	std::cout << "Enter Player's name: ";
	std::getline(std::cin, namePlayer);

	Match* match = nullptr;
	switch (keyInt)
	{
	case BOTEASY:
		match = new Match(namePlayer, "BOT", BOTEASY);
		break;
	case BOTNORMAL:
		match = new Match(namePlayer, "BOT", BOTNORMAL);
		break;
	case BOTHARD:
		match = new Match(namePlayer, "BOT", BOTHARD);
		break;
	default:
		break;
	}

	if (match != nullptr)
	{
		system("cls");
		match->start();
		delete match;
		system("pause");
	}
}

void Menu::replay()
{
	RecordAndReplay::Replay* replay = new RecordAndReplay::Replay();
	if (!replay->getListFromFile())
	{
		system("pause");
		return;
	}
	else
	{
		int numIndex;
		std::cout << "Enter number index of game match: "; std::cin >> numIndex;
		system("cls");
		replay->start(numIndex);
		delete replay;
		system("pause");
	}
}

void Menu::playerInformation()
{
	std::string key;
	do
	{
		system("cls");
		std::cout << YELLOW << "*-------" << RESET << "Play with BOT" << YELLOW << "-------*" << RESET << std::endl;
		std::cout << "Press number to choise:" << std::endl;
		std::cout << MAGENTA << "1.View" << RESET << " Rank Player" << std::endl;
		std::cout << MAGENTA << "2.Find" << RESET << " Player by name" << std::endl;
		std::cout << MAGENTA << "3.Find" << RESET << " Player with same 'level'" << std::endl;
		std::cout << MAGENTA << "4.Back" << RESET << " to MAIN MENU" << std::endl;
		std::getline(std::cin, key);
	} while (key.length() != 1 || (key[0] != '1'&& key[0] != '2' && key[0] != '3'&& key[0] != '4'));
	if (key[0] == '4')
	{
		return;
	}

	RecordPlayer* recordPlayer = new RecordPlayer();
	std::string namePlayer;
	switch (key[0])
	{
	case '1':
		recordPlayer->viewListRank();
		break;
	case '2':
		std::cout << "Enter name Player: ";		
		std::getline(std::cin, namePlayer);
		recordPlayer->findPlayerByName(namePlayer);
		break;
	case '3':
		std::cout << "Enter your name to search other player with same level: ";
		std::getline(std::cin, namePlayer);
		recordPlayer->findPlayerSameLevel(namePlayer);
		break;
	default:
		break;
	}
	delete recordPlayer;
	system("pause");
}

void Menu::guide()
{
	std::string text = std::string("- You can choose from 2 modes: against other players or against BOTs.\n\n")
		+ std::string("- 'Replays' are used to review historical matches.\n\n")
		+ std::string("- 'Player's Information' is used to view the rankings of players,\nsee information about players at the same level as you.\n\n")
		+ std::string("- Rules play: You need to move so that 4 consecutive moves in 1 straight\nline such as horizontal row, vertical row, or diagonal line\nbefore your opponent, you will win!\nIf your opponent makes 4 moves in a row ahead of you, he wins!\n\n");
	for (char c : text) {
		std::cout << c << std::flush;
		Sleep(40);
	}
	system("pause");
}

void Menu::start()
{
	SetConsoleFontSize(18);
	std::string key;
	while (true)
	{
		system("cls");
		std::cout << YELLOW << "*-------" << RESET << "MAIN MENU" << YELLOW << "-------*" << RESET << std::endl;
		std::cout << "Press number to choise:" << std::endl;
		std::cout << MAGENTA << "1.Play" << RESET << " with Other Player" << std::endl;
		std::cout << MAGENTA << "2.Play" << RESET << " with BOT" << std::endl;
		std::cout << MAGENTA << "3.Replay" << RESET << std::endl;
		std::cout << MAGENTA << "4.Player's" << RESET << " Information" << std::endl;
		std::cout << MAGENTA << "5.Guide" << RESET << std::endl;
		std::cout << MAGENTA << "6.Exit" << RESET << std::endl;
		std::getline(std::cin, key);
		if (key.length() != 1)
		{
			continue;
		}
		switch (key[0])
		{
		case '1':
			playWithOtherPlayer();
			break;
		case '2':
			playWithBot();
			break;
		case '3':
			replay();
			break;
		case '4':
			playerInformation();
			break;
		case '5':
			guide();
			break;
		case '6':
			return;
		default:
			break;
		}
	}


}

void Menu::SetConsoleFontSize(int fontSize) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                  
	cfi.dwFontSize.Y = fontSize;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
