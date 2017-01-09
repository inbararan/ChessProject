#pragma once

#include <string>

#include "Player.h"

using namespace std;

#define WHITE true
#define BLACK false

#define CURRENT (_currentPlayerIndicator)
#define OPPONENT (!_currentPlayerIndicator)

#define OK "0"
#define CHECK "1"
#define SRC_NOT_OCUUPIED "2"
#define DST_OCCUPIED "3"
#define MOVE_CAUSES_SELF_CHECK "4"
#define OUT_OF_BOARD "5"
#define ILLEGAL_MOVEMENT "6"
#define DST_EQL_SRC "7"
#define CHECKMATE "8"

typedef struct EnPassantDetails
{
	vector<Position> imaginaryPositions;
	int realUnitIdxInSet;
	bool isSet;
} EnPassantDetails;

typedef struct SimpleMove
{
	Unit* toBeMoved;
	Position dest;
};

typedef struct Move
{
	Unit* moved;
	Position source;
	Unit* taken;
} Move;

typedef struct MoveReport
{
	Unit* moved;				// Last unit moved
	bool promotionAvaliable;	// Is promotion avaliable for unit
	bool needsReopen;			// In cases of promotion, castling or en passant the frontend shoud reopen
} MoveReport;

class Game
{
private:
	Player _player1; // White
	Player _player2; // Black
	bool _currentPlayerIndicator; // true means player1
	EnPassantDetails _enPassantDetails;

	Player& getPlayer(bool playerIndicator);
	
	Move commitMove(Unit* toMove, Position dest, Player& opponent); // Commits move and return moev data for later use

	bool isDangeredBy(const Position& pos, bool playerIndicator);
	bool isDangeredBy(vector<Position> positions, bool playerIndicator);
	bool isCheckTo(bool playerIndicator);
	bool isCheckmate(); // To opponent

	bool castleIfAvaliable(CastlingType castlingType);

	vector<Position> getPath(Unit* unit, const Position& pos, bool playerIndicator);
	bool isClear(vector<Position> path);		// Path is clear of any unit

	void regret(Move move, Player& opponent);
public:
	Game();
	Game(const Game& other);

	string nextMove(string moveRepr, MoveReport& moveReport); // Returns code
	string getBoardRepr() const;
	bool promote(Unit* unit, char optionRepr); // Assuming promotion avaliable. Return value depends on optionRepr validity
};
