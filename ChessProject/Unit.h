#pragma once

#include <string>

#include "Position.h"

using namespace std;

enum CastlingType{ None, Long, Short };

typedef struct MovementFlags
{
	bool promotion;
	CastlingType castling;
	bool enPassant;
} MovementFlags;

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
	virtual vector<Position> pathToPosition(const Position& dest, bool enemyThere, Direction playerDirection) const; // Throws exception if dest unreachable
	virtual vector<Position> pathToPosition(const Position& dest, MovementFlags& flags, bool enemyThere, Direction playerDirection) const = 0; // Throws exception if dest unreachable
	void move(const Position& dest); // No validation, just moves.

	virtual bool canCommitEnPassant() const; // True on Pawn only
	virtual bool isCastlingAvaliable(CastlingType castlingType) const; // Relevant for King or Rook only
	virtual bool vital() const; // True for King only
};
