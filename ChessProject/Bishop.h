#include "Unit.h"

class Bishop : Unit
{
private:
	virtual char repr() const; // Actually `static` - indpendent of instance properties
public:
	Bishop(Position pos);
	virtual ~Bishop();

	// All overrides inherited methods from Unit:
	virtual vector<Position> pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const; // Throws exception if dest unreachable
	virtual void move(Position dest); // No validation, just moves.
};
