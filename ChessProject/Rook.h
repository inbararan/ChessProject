#include "Unit.h"

enum CastlingOption{None, Long, Short};

class Rook : Unit
{
private:
	bool moved;
	CastlingOption castlingOption;
public:
	// All inherited from Unit:
	virtual char repr() const; // Actually `static` - indpendent of instance properties
	virtual vector<Position> pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const; // Throws exception if dest unreachable
	virtual void move(Position dest); // No validation, just moves.

	virtual bool longCastlingAvaliable() const; // Returns true if big Rook
	virtual bool shortCastlingAvaliable() const; // Returns true if small Rook
};
