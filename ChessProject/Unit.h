#pragma once

#include <string>

#include "Position.h"

using namespace std;

#define DEFAULT_FLAGS {All,None,(Up|Down),false}

enum MovementAvaliabilty { Unreachable, Regular, Capture, All };
enum CastlingType { None, Long, Short };

typedef struct MovementFlags /*Flags and data the Game should know about movement option*/
{
	MovementAvaliabilty avaliability;	// Determines which way the movement is possible
	CastlingType castling;				// Determines castling type the move is done with (None if no castling involved)
	direction_t moveDirection;			// Bitwise variable. XXXXXX__. Left underscore bit represents the Up avaliabilty, right bit represents the Down.
	bool enPassantTarget;				// True if movement options makes the unit an en-passant target
} MovementFlags;

class Unit
{
protected:
	Position _pos;
	int _movesCount;

	virtual char repr() const = 0; // Lowercase, indpendent of instance properties
public:
	Unit(const Position& pos);

	const Position& getPos() const;

	char repr(bool toUpper) const; // Actually `static` - indpendent of instance properties
	virtual vector<Position> pathToPosition(const Position& dest, MovementFlags& flags) const = 0;
	void move(const Position& dest); // No validation, just moves.
	void regretMove(const Position& src); // Decreases _movesCount instead of increasing it
	bool moved() const;

	virtual bool vital() const; // True for King only
	virtual bool canPromote() const; // True on Pawn only
	virtual bool castlingRelevant(CastlingType castlingType, char& destFile) const; // For King and Rook only
};
