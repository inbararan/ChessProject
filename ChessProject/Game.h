#pragma once

#include <string>

#include "Player.h"

using namespace std;

#define WHITE true
#define BLACK false

#define PLAYER (_currentPlayerIndicator)
#define OPPONENT (!_currentPlayerIndicator)

#define OK "0"
#define CHECK "1"
#define SRC_NOT_OCUUPIED "2"
#define DST_OCCUPIED "3"
#define MOVE_CAUSES_SELF_CHECK "4"
#define OUT_OF_BOARD "5"
#define ILLEGAL_MOVEMENT "6"
#define DST_EQL_SRC "7"
#define CHEKMATE "8"

typedef struct EnPassantDetails
{
	vector<Position> imaginaryPositions;
	int realUnitIdxInSet;
	bool isSet;
} EnPassantDetails;

typedef struct Move
{
	Unit* moved;
	Position source;
	Unit* taken;
} Move;

class Game
{
private:
	Player _player1; // White
	Player _player2; // Black
	bool _currentPlayerIndicator; // true means player1
	EnPassantDetails _enPassantDetails;

	Player& getPlayer(bool playerIndicator);
	
	bool isCheckTo(bool playerIndicator);
	bool isCheckmateTo(bool playerIndicator);

	bool isClear(vector<Position> path);

	void regret(Move move);
public:
	Game();
	Game(const Game& other);

	string nextMove(string moveRepr); // Returns code
	string getBoardRepr() const;
};
