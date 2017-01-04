#pragma once

#include "Unit.h"

class Rook : public Unit
{
private:
	CastlingType _castlingAvaliablity;
	virtual char repr() const; // Actually `static` - indpendent of instance properties
public:
	Rook(Position pos, CastlingType _castlingAvaliablity);

	// All overrides inherited methods from Unit:
	virtual vector<Position> pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const; // Throws exception if dest unreachable

	virtual bool castlingAvaliable(CastlingType castlingType) const; // Autmatically returns true if not King or matching Rook
	virtual void commitCastling(CastlingType castlingType) const; // Does anything only if castlingType fits _castlingAvaliablity
};
