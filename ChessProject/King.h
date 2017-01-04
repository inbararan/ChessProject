#pragma once

#include "Unit.h"

class King : public Unit
{
private:
	virtual char repr() const; // Actually `static` - indpendent of instance properties
public:
	King(Position pos);

	// All overrides inherited methods from Unit:
	virtual vector<Position> pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const; // Throws exception if dest unreachable
	
	//virtual CastlingType avaliableCastling(Position dest) const; // Returns Long or Short if dest two squares to left or right from pos, else (or if King has moved) None
	//virtual void commitCastling(CastlingType castlingType) const;
	virtual bool vital() const;
};
