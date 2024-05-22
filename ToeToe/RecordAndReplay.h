#pragma once
#include<vector>
#include<string>
#include"File.h"
#include"DEFINE.h"


class RecordAndReplay
{
public:
	class Record
	{
	private:
		std::vector<int> coordinatesArr;
		int sizeBoard;
		int modePlay;
		int winer;
		std::string namePlayer1, namePlayer2;
	public:
		Record(int sizeBoard, int modePlay, std::string namePlayer1, std::string namePlayer2);
		~Record();

		void saveXY(int X, int Y);		// save position X,Y of player
		void savePlayerWin(int winer);
		void writeFile();				// save information to file
	};
	class Replay
	{
	private:
		std::vector<std::string> matchList;
	public:
		Replay();
		~Replay();

		bool getListFromFile();			// get date from file
		bool start(int stt);			// replay match
	};
};

