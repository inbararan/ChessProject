#include "Unit.h"

class Knight : Unit
{
private:
	virtual char repr() const; // Actually `static` - indpendent of instance properties
public:
	Knight(Position pos);
	virtual ~Knight();

	// All overrides inherited methods from Unit:
	virtual vector<Position> pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const; // Throws exception if dest unreachable
};
