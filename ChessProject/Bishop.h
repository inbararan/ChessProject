#pragma once

#include "Unit.h"
#include <algorithm>

class Bishop : public Unit
{
private:
	virtual char repr() const; // Actually `static` - indpendent of instance properties
public:
	Bishop(const Position& pos);
	virtual ~Bishop();

	// All overrides inherited methods from Unit:
	virtual vector<Position> pathToPosition(const Position& dest, MovementFlags& flags) const ;
};
