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

typedef struct SimpleMove /*Saving move description for saving moving options*/
{
	Unit* toBeMoved;	// Unit to be moved
	Position dest;		// Position the unit shall be moved to
} SimpleMove;

typedef struct FullMove /*Saving a move's consequences after it happend, for the option to regret*/
{
	Unit* moved;		// The unit that has moved
	Position source;	// The initial position of moved unit
	Unit* taken;		// The unit that was taken (nullptr if no unit was taken)
} FullMove;

typedef struct MoveReport /*Flags and data about things the main program should be aware of*/
{
	Unit* moved;				// Last moved unit
	bool promotionAvaliable;	// Is promotion avaliable for moved unit
	bool needsReopen;			// In cases of promotion, castling or en passant the frontend shoud reopen
} MoveReport;

class Game
{
private:
	Player _player1; // White
	Player _player2; // Black
	bool _currentPlayerIndicator; // true means player1

	Player& getPlayer(bool playerIndicator);
	
	FullMove commitMove(Unit* toMove, Position dest, Player& opponent); // Commits move and return moev data for later use

	bool isDangeredBy(const Position& pos, bool playerIndicator);
	bool isDangeredBy(vector<Position> positions, bool playerIndicator);
	bool isCheckTo(bool playerIndicator);
	bool isCheckmate(); // To opponent

	bool castleIfAvaliable(CastlingType castlingType);

	vector<Position> getPath(Unit* unit, const Position& dest, bool opponentIndicator);
	vector<Position> getPath(Unit* unit, bool enemyThereToPush, const Position& dest);
	vector<Position> getPath(Unit* unit, MovementFlags& flags, bool enemyThere, const Position& dest);
	vector<Position> getPath(Unit* unit, MovementFlags& flags, const Position& dest, bool opponentIndicator);
	bool isClear(vector<Position> path);		// Path is clear of any unit

	void regret(FullMove move, Player& opponent);

	void validateMoveLegality(Unit* unit, const Position& dest, MoveReport& report);
public:
	Game();
	Game(const Game& other);

	string nextMove(string moveRepr, MoveReport& report); // Returns code
	string getBoardRepr() const;
	bool promote(Unit* unit, char optionRepr); // Assuming promotion avaliable. Return value depends on optionRepr validity
};
