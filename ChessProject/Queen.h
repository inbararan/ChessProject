#include "Unit.h"

class Queen
{
public:
	Queen(Position pos);
	virtual ~Queen();

	// All overrides inherited methods from Unit:
	virtual char repr() const; // Actually `static` - indpendent of instance properties
	virtual vector<Position> pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const; // Throws exception if dest unreachable
	virtual void move(Position dest); // No validation, just moves.
};