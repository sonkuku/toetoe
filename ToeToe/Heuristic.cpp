#include "Heuristic.h"
#include <ctime>

#include "DEFINE.h"

Heuristic::Heuristic()
{
    srand(static_cast<unsigned int>(time(0)));
    this->countMove = 0;
}
Heuristic::~Heuristic()
{
}

void Heuristic::setSize(int size)
{
    this->size = size;
}


void Heuristic::setBoard()
{
    board.resize(this->size);
    for (int i = 0; i < this->size; ++i)
    {
        board[i].resize(this->size);
    }

    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            this->board[i][j] = NO_PLAYER;
        }
    }
}

void Heuristic::setEasy(bool easy)
{
    this->easy = easy;
}

void Heuristic::setHumanMove(int x, int y)
{
    if (x == -1 || y == -1)
    {
        return;
    }
    board[x][y] = PLAYER_1;
}


vector<long long> Heuristic::check(const int currentX, const int currentY, int playerMove) {

    auto count_sequence = [&](int dx, int dy, int& length, int& open_ends)
    {
        int i, j;
        int count1 = 0, count2 = 0;
        for (i = currentX + dx, j = currentY + dy; i >= 0 && j >= 0 && i < this->size && j < this->size && board[i][j] == playerMove; i += dx, j += dy)
            count1++;
        int left_open = (i >= 0 && j >= 0 && i < this->size && j < this->size && board[i][j] == NO_PLAYER);

        for (i = currentX - dx, j = currentY - dy; i >= 0 && j >= 0 && i < this->size && j < this->size && board[i][j] == playerMove; i -= dx, j -= dy)
            count2++;
        int right_open = (i >= 0 && j >= 0 && i < this->size && j < this->size && board[i][j] == NO_PLAYER);

        length = count1 + count2 + 1;
        open_ends = left_open + right_open;
    };

    int stat[8] = { 0 }; // even elements are numbers playerMove, odd elements are numbers open(1 or 2)

    // Check 8 direction
    count_sequence(1, 0, stat[0], stat[1]);
    count_sequence(0, 1, stat[2], stat[3]);
    count_sequence(1, 1, stat[4], stat[5]);
    count_sequence(1, -1, stat[6], stat[7]);

    vector<long long> result(6, 0);
    for (int i = 0; i < 8; i += 2) {
        result[0] += (stat[i] >= 4);                     // 4 moves is win
        result[1] += (stat[i] == 3 && stat[i + 1] == 2); // 3 moves and 2 open

        result[2] += (stat[i] == 3 && stat[i + 1] == 1); // 3 moves and 1 open
        result[3] += (stat[i] == 2 && stat[i + 1] == 2); // 2 moves and 2 open

        result[4] += (stat[i] == 2 && stat[i + 1] == 1); // 2 moves and 1 open
        result[5] += (stat[i] == 1 && stat[i + 1] == 1); // 1 moves and 1 open
    }

    return result;
}


Positionn Heuristic::getMove() {
    std::map <long long, Positionn, std::greater<long long> > weight;
    vector < Positionn > listsPositionMove;

    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            if (board[i][j] == NO_PLAYER) // no player moved this position
            {
                std::vector <long long> pointBot = check(i, j, PLAYER_2);
                std::vector <long long> pointHuman = check(i, j, PLAYER_1);

                long long a = pointBot[0] * 20000 + pointHuman[0] * 10000 + pointBot[1] * 5000 + pointHuman[1] * 2000 + pointBot[2] * 1000 + pointHuman[2] * 321 + pointBot[3] * 500;
                if (a > 0)// a always >= 0
                {
                    long long b = pointHuman[3] * 3 + pointBot[4] * 5 + pointBot[5] * 5 + pointHuman[4] * 4 + pointHuman[5] * 1;
                    weight[a + b] = std::make_pair(i, j);
                }
            }
        }
    }
    for (auto it = weight.begin(); it != weight.end(); ++it)
    {
        listsPositionMove.push_back(it->second);
    }
    if (!listsPositionMove.empty())
    {
        if (!this->easy)
        {
            return listsPositionMove[0];
        }
        else
        {
            return listsPositionMove[0 + rand() % (listsPositionMove.size())];
        }
    }


    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            if (board[i][j] == NO_PLAYER)
            {
                int X, Y;
                for (int dir = 0; dir < 8; ++dir)
                {
                    X = (i + direction[dir][0]);
                    Y = (j + direction[dir][1]);
                    if (X >= 0 && X < this->size && Y >= 0 && Y < this->size && board[X][Y] != NO_PLAYER)
                    {
                        listsPositionMove.push_back(std::make_pair(i, j));
                        break;
                    }
                }
            }
        }
    }
    if (!listsPositionMove.empty())
    {
        return listsPositionMove[0 + rand() % (listsPositionMove.size())];
    }
    else
    {
        if (this->countMove == 0)
        {
            int randNum1 = -1 + rand() % (1 + 1 + 1);
            int randNum2 = -1 + rand() % (1 + 1 + 1);
            return Positionn(this->size / 2 + randNum1, this->size / 2 + randNum2);
        }
    }

    int x, y;
    do
    {
        x = rand() % this->size;
        y = rand() % this->size;
    } while (board[x][y] != NO_PLAYER);
    return Positionn(x, y);
}

Positionn Heuristic::makeMove() {
    Positionn move = getMove();
    board[move.ROW][move.COL] = PLAYER_2;
    this->countMove++;
    return move;
}
