#pragma once

#include <string>

#include "Player.h"

using namespace std;

typedef struct EnPassantDetails
{
	vector<Position> imaginaryPositions;
	int realUnitIdxInSet;
	bool isSet;
} EnPassantDetails;

class Game
{
private:
	Player player1; // White
	Player player2; // Black
	bool currentPlayerIndicator; // true means player1
	EnPassantDetails enPassantDetails;

	Player& currentPlayer();
	Player& currentOpponent();
	bool isCheck(bool currentPlayer);
	bool isCheckmate();
public:
	Game();
	Game(const Game& other);
	~Game();

	string nextMove(string moveRepr); // Returns code
	string getBoardRepr() const;
};
