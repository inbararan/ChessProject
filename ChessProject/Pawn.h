#pragma once

#include "Unit.h"
#include <algorithm>

class Pawn : public Unit
{
private:
	virtual char repr() const; // Actually `static` - indpendent of instance properties
public:
	Pawn(const Position& pos);

	// All overrides inherited methods from Unit:
	virtual vector<Position> pathToPosition(const Position& dest, MovementFlags& flags) const;

	virtual bool canPromote() const;
};
