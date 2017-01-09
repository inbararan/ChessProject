#pragma once

#include "Unit.h"

class Knight : public Unit
{
private:
	virtual char repr() const; // Actually `static` - indpendent of instance properties
	bool isReachable(Position dest) const;
public:
	Knight(const Position& pos);

	// All overrides inherited methods from Unit:
	virtual vector<Position> pathToPosition(const Position& dest, MovementFlags& flags, bool enemyThere) const; // Throws exception if dest unreachable
};
