#pragma once

#include "Unit.h"
#include "Exceptions.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public Unit
{
private:
	virtual char repr() const; // Actually `static` - indpendent of instance properties
public:
	Queen(const Position& pos);

	// All overrides inherited methods from Unit:
	virtual vector<Position> pathToPosition(const Position& dest, MovementFlags& flags) const;
};
