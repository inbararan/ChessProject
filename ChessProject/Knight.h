#include "Unit.h"

class Knight : public Unit
{
private:
	virtual char repr() const; // Actually `static` - indpendent of instance properties
	bool isReachable(Position dest) const;
public:
	Knight(Position pos);

	// All overrides inherited methods from Unit:
	virtual vector<Position> pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const; // Throws exception if dest unreachable
};
