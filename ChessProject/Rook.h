#pragma once

#include "Unit.h"

class Rook : public Unit
{
private:
	CastlingType _castlingAvaliablity;
	virtual char repr() const; // Actually `static` - indpendent of instance properties
public:
	Rook(const Position& pos);
	Rook(const Position& pos, CastlingType castlingAvaliablity);

	// All overrides inherited methods from Unit:
	virtual vector<Position> pathToPosition(const Position& dest, MovementFlags& flags, bool enemyThere, Direction playerDirection) const; // Throws exception if dest unreachable
};
