#pragma once
#include <vector>
#include <utility>
#include <map>

using std::vector;
using std::pair;

#define Positionn pair<int, int>
#define ROW first
#define COL second

// this class use to evaluation the right move of BOT player
class Heuristic {
public:
	Heuristic();
	~Heuristic();

	void setSize(int size); // set size of board
	void setBoard();		// init board
	void setEasy(bool easy);
	void setHumanMove(int x, int y);
	Positionn makeMove();	// move and return Position X,Y
private:
	vector <long long> check(const int currentX, const int currentY, int playerMove); // get data for analysis
	Positionn getMove();	// analyze and return Position X,Y

	int size;
	vector< vector<int> > board;
	bool easy;
	int countMove;
};


