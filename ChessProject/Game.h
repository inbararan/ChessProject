#pragma once

#include <string>

#include "Player.h"

using namespace std;

#define WHITE true
#define BLACK false

typedef struct EnPassantDetails
{
	vector<Position> imaginaryPositions;
	int realUnitIdxInSet;
	bool isSet;
} EnPassantDetails;

class Game
{
private:
	Player _player1; // White
	Player _player2; // Black
	bool _currentPlayerIndicator; // true means player1
	EnPassantDetails _enPassantDetails;

	Player& currentPlayer();
	Player& currentOpponent();
	bool isCheckTo(bool currentPlayer);
	bool isCheckmateTo(bool currentPlayer);
public:
	Game();
	Game(const Game& other);
	~Game();

	string nextMove(string moveRepr); // Returns code
	string getBoardRepr() const;
};
