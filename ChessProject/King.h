#pragma once

#include "Unit.h"

class King : public Unit
{
private:
	virtual char repr() const; // Actually `static` - indpendent of instance properties
public:
	King(const Position& pos);

	// All overrides inherited methods from Unit:
	virtual vector<Position> pathToPosition(const Position& dest, MovementFlags& flags, bool enemyThere, Direction playerDirection) const; // Throws exception if dest unreachable

	virtual bool vital() const;
};
