#pragma once
#include<map>
#include<string>
#include<vector>
#include<string>
#include"DEFINE.h"

class RecordPlayer
{
private:
	
	// this class used for store score of player
	class ScorePlayer
	{
	public:
		ScorePlayer(std::string namePlayer, int numOfWins, int numOfLosses, int numOfDraws);
		~ScorePlayer();
		std::string namePlayer;
		int numOfWins, numOfLosses, numOfDraws;
		float percentWin, percentLoss, percentDraws;

		static bool compareByPercentWinDescending(const ScorePlayer* a, const ScorePlayer* b);
		bool operator<(const ScorePlayer& other) const;
	};
private:
	std::vector<ScorePlayer*> playerScoreList;
public:
	RecordPlayer();
	~RecordPlayer();

	bool getListFromFile();
	void writeFile(std::string namePlayer1, std::string namePlayer2, int whoWin);
	
	void viewListRank();
	void findPlayerByName(std::string namePlayer);
	void findPlayerSameLevel(std::string namePlayer);

};

