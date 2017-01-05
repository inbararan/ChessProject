#pragma once

#include <string>

#include "Position.h"

using namespace std;

typedef struct MovementFlags
{
	bool promotion;
	bool castling;
	bool enPassant;
} MovementFlags;

enum CastlingType{ None, Long, Short };

class Unit
{
protected:
	Position _pos;
	bool _moved;

	virtual char repr() const = 0; // Lowercase, indpendent of instance properties
public:
	Unit(const Position& pos);

	const Position& getPos() const;

	char repr(bool toUpper) const; // Actually `static` - indpendent of instance properties
	virtual vector<Position> pathToPosition(const Position& dest, MovementFlags& flags, bool enemyThere, Direction playerDirection) const = 0; // Throws exception if dest unreachable
	void move(const Position& dest); // No validation, just moves.

	virtual bool canCommitEnPassant() const; // True on Pawn only
	virtual bool vital() const; // True for King only
};
