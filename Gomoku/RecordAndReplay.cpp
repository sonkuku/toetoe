#include "RecordAndReplay.h"
#include<iostream>

#include"Draw.h"
#include"DEFINE.h"


RecordAndReplay::Record::Record(int sizeBoard, int modePlay, std::string namePlayer1, std::string namePlayer2) :
	sizeBoard(sizeBoard), modePlay(modePlay), namePlayer1(namePlayer1), namePlayer2(namePlayer2)
{
}

RecordAndReplay::Record::~Record()
{
}

void RecordAndReplay::Record::saveXY(int X, int Y)
{
	// save X, Y move of player
	coordinatesArr.push_back(X);
	coordinatesArr.push_back(Y);
}

void RecordAndReplay::Record::savePlayerWin(int winer)
{
	this->winer = winer;
}

void RecordAndReplay::Record::writeFile()
{
	// write data to file in format
	std::string stringWrite;
	stringWrite.append(std::to_string(sizeBoard));
	stringWrite.append(",");
	stringWrite.append(std::to_string(modePlay));
	stringWrite.append(",");
	stringWrite.append(namePlayer1);
	stringWrite.append(",");
	stringWrite.append(namePlayer2);
	stringWrite.append(",");
	stringWrite.append(std::to_string(winer));
	for (int i : coordinatesArr)
	{
		stringWrite.append(",");
		stringWrite.append(std::to_string(i));
	}
	File::writeFile(fileLogMatch, stringWrite);
}

RecordAndReplay::Replay::Replay()
{
}

RecordAndReplay::Replay::~Replay()
{
}

bool RecordAndReplay::Replay::getListFromFile()
{
	File::readFile(fileLogMatch, matchList);
	if (matchList.empty())
	{
		std::cout << "No History Match!" << std::endl;
		return false;
	}
	else
	{
		std::cout << "---History---" << std::endl;
		for (int i = 0; i < matchList.size(); ++i)
		{
			std::string line = matchList[i];
			if (line == "")
			{
				continue;
			}
			std::string buffArr[4];
			size_t index = 1;			
			for (int j = 0; j < 4; ++j)
			{
				size_t start = line.find_first_of(",", index);
				size_t end = line.find_first_of(",", start + 1);
				index = end;
				buffArr[j] = line.substr(start + 1, end - start - 1);
			}
			
			std::string str;
			switch (std::stoi(buffArr[0]))
			{
			case 0:
				str = "PLAYER SOLO";
				break;
			case 1:
				str = "BOT EASY";
				break;
			case 2:
				str = "BOT NORMAL";
				break;
			case 3:
				str = "BOT HARD";
				break;
			default:
				break;
			}
			str = str + ": " + buffArr[1] + " - " + buffArr[2];
			if (std::stoi(buffArr[3]) == GAME_DRAW)
			{
				str += " - draw";
			}
			else if (std::stoi(buffArr[3]) == PLAYER_1)
			{
				str += " - " + buffArr[1] + " win";
			}
			else if (std::stoi(buffArr[3]) == PLAYER_2)
			{
				str += " - " + buffArr[2] + " win";
			}
			std::cout << i << ". " << str << std::endl;
		}
	}
	return true;
}

bool RecordAndReplay::Replay::start(int stt)
{
	if (stt >= (int)matchList.size() - 1)
	{
		std::cout << "You enter not correct number game!" << std::endl;
		return false;
	}

	std::string line = matchList[stt];
	std::string buffArr[5];
	size_t index = -1;
	for (int i = 0; i < 5; ++i)
	{
		size_t start = line.find_first_of(",", index);
		size_t end = line.find_first_of(",", start + 1);
		index = end;
		buffArr[i] = line.substr(start + 1, end - start - 1);
	}

	Draw::setNamePlayer(buffArr[2], buffArr[3]);
	Draw::drawBoard(std::stoi(buffArr[0]));
	int X, Y;
	int player = 1;
	if (std::stoi(buffArr[1]) == BOTHARD)
	{
		player = 2; // bot move first
	}
	while (index != std::string::npos)
	{
		size_t start = line.find_first_of(",", index);
		size_t end = line.find_first_of(",", start + 1);
		index = end;
		X = stoi(line.substr(start + 1, end - start - 1));

		start = line.find_first_of(",", index);
		end = line.find_first_of(",", start + 1);
		index = end;
		Y = stoi(line.substr(start + 1, end - start - 1));

		if (player == 1)
		{			
			Draw::insertX(X, Y);
			std::cout << "Player " << buffArr[2] << "'s turn: " << X << " " << Y;
			player = 2;
		}
		else
		{
			Draw::insertO(X, Y);
			std::cout << "Player " << buffArr[3] << "'s turn: " << X << " " << Y;
			player = 1;
		}

		Sleep(1000);
	}
	Draw::gotoCurrentCursorAndClearLine();

	int winer = std::stoi(buffArr[4]);
	if (winer == GAME_DRAW) {
		std::cout << "Game is draw!" << std::endl;
	}
	else if (winer == PLAYER_1) {
		std::cout << "Player " << buffArr[2] << " win!" << std::endl;
	}
	else if (winer == PLAYER_2) {
		std::cout << "Player " << buffArr[3] << " win!" << std::endl;
	}
	
	return true;
}
