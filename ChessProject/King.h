#include "Unit.h"

class King
{
private:
	bool moved;
public:
	King(Position pos);
	virtual ~King();

	// All inherited from Unit:
	virtual char repr() const; // Actually `static` - indpendent of instance properties
	virtual vector<Position> pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const; // Throws exception if dest unreachable
	virtual void move(Position dest); // No validation, just moves.

	virtual bool longCastlingAvaliable() const; // Returns true if didn't moved
	virtual bool shortCastlingAvaliable() const; // Returns true if didn't moved
};
};
