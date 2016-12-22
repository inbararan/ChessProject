#pragma once

#include <string>

#include "Player.h"

using namespace std;

#define PLAYERS_NUM 2
#define OTHER(p) (PLAYERS_NUM - p)

typedef struct EnPassantDetails
{
	Position imaganaryPos;
	int candidateIdxInSet;
} EnPassantDetails;

class Game
{
private:
	Player players[PLAYERS_NUM];
	int currPlayerIdx;
	EnPassantDetails enPassantDetails;

	bool isCheck(int playerIdx);
	bool isCheckmate();
public:
	Game();
	Game(const Game& other);
	~Game();

	int nextMove(string moveRepr); // Returns code
	string getBoardRepr() const;
};
