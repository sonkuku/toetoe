#include"RecordPlayer.h"
#include<algorithm>
#include<iostream>
#include<iomanip>

#include"File.h"
#include"DEFINE.h"

RecordPlayer::RecordPlayer()
{
	std::cout << std::fixed << std::setprecision(2);
}

RecordPlayer::~RecordPlayer()
{
	if (!playerScoreList.empty())
	{
		for (ScorePlayer* playerScore : playerScoreList)
		{
			if (playerScore != nullptr)
				delete playerScore;
		}
		playerScoreList.clear();
	}
}

bool RecordPlayer::getListFromFile()
{
	if (!playerScoreList.empty())
	{
		for (ScorePlayer* playerScore : playerScoreList)
		{
			if (playerScore != nullptr)
				delete playerScore;	
		}
		playerScoreList.clear();
	}

	std::vector<std::string> playerScoreListString;
	File::readFile(fileLogScorePlayer, playerScoreListString);
	if (playerScoreListString.empty())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < playerScoreListString.size(); ++i)
		{
			std::string line = playerScoreListString[i];
			if (line == "")
			{
				continue;
			}
			std::string buffArr[4];
			size_t index = -1;
			for (int i = 0; i < 4; ++i)
			{
				size_t start = line.find_first_of(",", index);
				size_t end = line.find_first_of(",", start + 1);
				index = end;
				buffArr[i] = line.substr(start + 1, end - start - 1);
			}
			playerScoreList.push_back(new ScorePlayer(buffArr[0], std::stoi(buffArr[1]), std::stoi(buffArr[2]), std::stoi(buffArr[3])));
		}

		std::sort(playerScoreList.begin(), playerScoreList.end(), ScorePlayer::compareByPercentWinDescending);

	}
	return true;
}

void RecordPlayer::writeFile(std::string namePlayer1, std::string namePlayer2, int whoWin)
{
	std::vector<std::string> playerScoreListString;
	File::readFile(fileLogScorePlayer, playerScoreListString);
	if (playerScoreListString.empty())
	{
		if (whoWin == GAME_DRAW)
		{
			File::writeFile(fileLogScorePlayer, namePlayer1 + ",0,0,1");
			File::writeFile(fileLogScorePlayer, namePlayer2 + ",0,0,1");
		}
		else if (whoWin == PLAYER_1)
		{
			File::writeFile(fileLogScorePlayer, namePlayer1 + ",1,0,0");
			File::writeFile(fileLogScorePlayer, namePlayer2 + ",0,1,0");
		}
		else if (whoWin == PLAYER_2)
		{
			File::writeFile(fileLogScorePlayer, namePlayer1 + ",0,1,0");
			File::writeFile(fileLogScorePlayer, namePlayer2 + ",1,0,0");
		}
	}
	else
	{
		bool existPlayer1 = false, existPlayer2 = false;
		for (int i = 0; i < playerScoreListString.size(); ++i)
		{
			std::string line = playerScoreListString[i];
			if (line == "")
			{
				continue;
			}
			std::string buffArr[4];
			size_t index = -1;
			for (int i = 0; i < 4; ++i)
			{
				size_t start = line.find_first_of(",", index);
				size_t end = line.find_first_of(",", start + 1);
				index = end;
				buffArr[i] = line.substr(start + 1, end - start - 1);
			}

			if (buffArr[0] == namePlayer1 || buffArr[0] == namePlayer2)
			{
				if (buffArr[0] == namePlayer1)
				{
					existPlayer1 = true;
				}
				else if (buffArr[0] == namePlayer2)
				{
					existPlayer2 = true;
				}

				if (whoWin == GAME_DRAW)
				{
					int numOfDraws = std::stoi(buffArr[3]);
					++numOfDraws;
					buffArr[3] = std::to_string(numOfDraws);
				}
				else
				{
					int numOfWins = std::stoi(buffArr[1]);
					int numOfLosses = std::stoi(buffArr[2]);
					if ((whoWin == PLAYER_1 && buffArr[0] == namePlayer1) || (whoWin == PLAYER_2 && buffArr[0] == namePlayer2))
					{
						++numOfWins;
					}
					else
					{
						++numOfLosses;
					}
					buffArr[1] = std::to_string(numOfWins);
					buffArr[2] = std::to_string(numOfLosses);
				}
				playerScoreListString[i] = buffArr[0] + "," + buffArr[1] + "," + buffArr[2] + "," + buffArr[3];
			}
		}

		if (existPlayer1 || existPlayer2)
		{
			File::deleteFile(fileLogScorePlayer);
			for (int i = 0; i < playerScoreListString.size(); ++i)
			{
				if (playerScoreListString[i] != "")
					File::writeFile(fileLogScorePlayer, playerScoreListString[i]);
			}
		}

		if (!existPlayer1)
		{
			if (whoWin == GAME_DRAW)
			{
				File::writeFile(fileLogScorePlayer, namePlayer1 + ",0,0,1");
			}
			else if (whoWin == PLAYER_1)
			{
				File::writeFile(fileLogScorePlayer, namePlayer1 + ",1,0,0");
			}
			else if (whoWin == PLAYER_2)
			{
				File::writeFile(fileLogScorePlayer, namePlayer1 + ",0,1,0");
			}
		}
		if (!existPlayer2)
		{
			if (whoWin == GAME_DRAW)
			{
				File::writeFile(fileLogScorePlayer, namePlayer2 + ",0,0,1");
			}
			else if (whoWin == PLAYER_1)
			{
				File::writeFile(fileLogScorePlayer, namePlayer2 + ",0,1,0");
			}
			else if (whoWin == PLAYER_2)
			{
				File::writeFile(fileLogScorePlayer, namePlayer2 + ",1,0,0");
			}
		}

	}
}

void RecordPlayer::viewListRank()
{
	if (!getListFromFile())
	{
		std::cout << "No History Player!" << std::endl;
	}
	else
	{
		std::cout << "---Rank---" << std::endl;
		std::cout << std::setw(5) << std::left << "Top";
		std::cout << std::setw(15) << std::left << "Name player";
		std::cout << std::setw(10) << std::left << "Wins";
		std::cout << std::setw(10) << std::left << "Losses";
		std::cout << std::setw(10) << std::left << "Draws";
		std::cout << std::setw(10) << std::left << "Win Rate(%)";
		std::cout << std::endl;
		for (int i = 0; i < playerScoreList.size();++i)
		{
			std::cout << std::setw(5) << std::left << i+1;
			std::cout << std::setw(15) << std::left << playerScoreList[i]->namePlayer;
			std::cout << std::setw(10) << std::left << playerScoreList[i]->numOfWins;
			std::cout << std::setw(10) << std::left << playerScoreList[i]->numOfLosses;
			std::cout << std::setw(10) << std::left << playerScoreList[i]->numOfDraws;
			std::cout << std::setw(10) << std::left << playerScoreList[i]->percentWin;
			std::cout << std::endl;
		}
	}
}

void RecordPlayer::findPlayerByName(std::string namePlayer)
{
	if (!getListFromFile())
	{
		std::cout << "No Player!" << std::endl;
	}
	else
	{
		for (int i = 0; i < playerScoreList.size(); ++i)
		{
			if (playerScoreList[i]->namePlayer == namePlayer)
			{
				std::cout << std::setw(5) << std::left << "Top";
				std::cout << std::setw(15) << std::left << "Name player";
				std::cout << std::setw(10) << std::left << "Wins";
				std::cout << std::setw(10) << std::left << "Losses";
				std::cout << std::setw(10) << std::left << "Draws";
				std::cout << std::setw(10) << std::left << "Win Rate(%)";
				std::cout << std::endl;
				std::cout << std::setw(5) << std::left << i + 1;
				std::cout << std::setw(15) << std::left << playerScoreList[i]->namePlayer;
				std::cout << std::setw(10) << std::left << playerScoreList[i]->numOfWins;
				std::cout << std::setw(10) << std::left << playerScoreList[i]->numOfLosses;
				std::cout << std::setw(10) << std::left << playerScoreList[i]->numOfDraws;
				std::cout << std::setw(10) << std::left << playerScoreList[i]->percentWin;
				std::cout << std::endl;
				return;
			}
		}
		std::cout << "No Player!" << std::endl;
	}
}

void RecordPlayer::findPlayerSameLevel(std::string namePlayer)
{
	if (!getListFromFile())
	{
		std::cout << "No Player: " << namePlayer << std::endl;
	}
	else
	{
		ScorePlayer* playerFind = nullptr;
		for (int i = 0; i < playerScoreList.size(); ++i)
		{
			if (playerScoreList[i]->namePlayer == namePlayer)
			{
				playerFind = playerScoreList[i];
				break;
			}
		}
		if (playerFind == nullptr)
		{
			std::cout << "No Player: " << namePlayer << std::endl;
			return;
		}

		std::vector<ScorePlayer*> playerScoreListDescendPercentWin;
		playerScoreListDescendPercentWin.assign(playerScoreList.begin(), playerScoreList.end());
		std::sort(playerScoreListDescendPercentWin.begin(), playerScoreListDescendPercentWin.end(), [](const ScorePlayer* obj1, const ScorePlayer* obj2)
			{
				return obj1->percentWin > obj2->percentWin;
			});
		int indexPlayerScoreWinSame = -1;
		for (int i = 0; i < playerScoreListDescendPercentWin.size(); ++i)
		{
			if (playerScoreListDescendPercentWin[i] == playerFind)
			{
				int prev = i - 1, next = i + 1;
				if (prev >= 0 && next < playerScoreListDescendPercentWin.size())
				{
					if (playerScoreListDescendPercentWin[prev] - playerScoreListDescendPercentWin[i]
				> playerScoreListDescendPercentWin[i] - playerScoreListDescendPercentWin[next])
					{
						indexPlayerScoreWinSame = next;
					}
					else
					{
						indexPlayerScoreWinSame = prev;
					}
				}
				else if (prev >= 0)
				{
					indexPlayerScoreWinSame = prev;
				}
				else if (next < playerScoreListDescendPercentWin.size())
				{
					indexPlayerScoreWinSame = next;
				}
			}
		}

		std::vector<ScorePlayer*> playerScoreListDescendPercentLoss;
		playerScoreListDescendPercentLoss.assign(playerScoreList.begin(), playerScoreList.end());
		std::sort(playerScoreListDescendPercentLoss.begin(), playerScoreListDescendPercentLoss.end(), [](const ScorePlayer* obj1, const ScorePlayer* obj2)
			{
				return obj1->percentLoss > obj2->percentLoss;
			});
		int indexPlayerScoreLossSame = -1;
		for (int i = 0; i < playerScoreListDescendPercentLoss.size(); ++i)
		{
			if (playerScoreListDescendPercentLoss[i] == playerFind)
			{
				int prev = i - 1, next = i + 1;
				if (prev >= 0 && next < playerScoreListDescendPercentLoss.size())
				{
					if (playerScoreListDescendPercentLoss[prev] - playerScoreListDescendPercentLoss[i]
				> playerScoreListDescendPercentLoss[i] - playerScoreListDescendPercentLoss[next])
					{
						indexPlayerScoreLossSame = next;
					}
					else
					{
						indexPlayerScoreLossSame = prev;
					}
				}
				else if (prev >= 0)
				{
					indexPlayerScoreLossSame = prev;
				}
				else if (next < playerScoreListDescendPercentLoss.size())
				{
					indexPlayerScoreLossSame = next;
				}
			}
		}

		if (indexPlayerScoreWinSame == -1 && indexPlayerScoreLossSame == -1)
		{
			std::cout << "No find player with same level!" << std::endl;
		}
		else
		{
			std::cout << "You: " << std::endl;
			std::cout << playerFind->namePlayer << ": "
				<< playerFind->percentWin << " % win" << std::endl;
			std::cout << playerFind->namePlayer << ": "
				<< playerFind->percentLoss << " % loss" << std::endl;
			std::cout << std::endl;
			if (indexPlayerScoreWinSame != -1 && indexPlayerScoreLossSame != -1)
			{
				std::cout << "Find player: " << std::endl;
				std::cout << playerScoreListDescendPercentWin[indexPlayerScoreWinSame]->namePlayer << ": "
					<< playerScoreListDescendPercentWin[indexPlayerScoreWinSame]->percentWin << " % win" << std::endl;
				std::cout << playerScoreListDescendPercentLoss[indexPlayerScoreLossSame]->namePlayer << ": "
					<< playerScoreListDescendPercentLoss[indexPlayerScoreLossSame]->percentLoss << " % loss" << std::endl;
			}
			else if (indexPlayerScoreWinSame != -1)
			{
				std::cout << "Find player: " << std::endl;
				std::cout << playerScoreListDescendPercentWin[indexPlayerScoreWinSame]->namePlayer << ": "
					<< playerScoreListDescendPercentWin[indexPlayerScoreWinSame]->percentWin << " % win" << std::endl;
			}
			else if (indexPlayerScoreLossSame != -1)
			{
				std::cout << "Find player: " << std::endl;
				std::cout << playerScoreListDescendPercentLoss[indexPlayerScoreLossSame]->namePlayer << ": "
					<< playerScoreListDescendPercentLoss[indexPlayerScoreLossSame]->percentLoss << " % loss" << std::endl;
			}
		}
		

	}
}




RecordPlayer::ScorePlayer::ScorePlayer(std::string namePlayer, int numOfWins, int numOfLosses, int numOfDraws):
	namePlayer(namePlayer), numOfWins(numOfWins), numOfLosses(numOfLosses), numOfDraws(numOfDraws)
{
	percentWin = ((float)(numOfWins) / (float)(numOfWins + numOfLosses + numOfDraws)) * 100;
	percentLoss = ((float)(numOfLosses) / (float)(numOfWins + numOfLosses + numOfDraws)) * 100;
	percentDraws = ((float)(numOfDraws) / (float)(numOfWins + numOfLosses + numOfDraws)) * 100;
}

RecordPlayer::ScorePlayer::~ScorePlayer()
{
}

bool RecordPlayer::ScorePlayer::compareByPercentWinDescending(const ScorePlayer* a, const ScorePlayer* b)
{
	if (a->percentWin == b->percentWin)
	{
		if (a->numOfWins == b->numOfWins)
		{
			return a->numOfLosses < b->numOfLosses;
		}
		return a->numOfWins > b->numOfWins;
	}
	return a->percentWin > b->percentWin;
}

bool RecordPlayer::ScorePlayer::operator<(const ScorePlayer& other) const
{
	return this->percentWin < other.percentWin;
}

