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

	virtual CastlingType avaliableCastling(Position dest) const; // Returns Long or Short if dest two squares to left or right from pos, else (or if King has moved) None
};
