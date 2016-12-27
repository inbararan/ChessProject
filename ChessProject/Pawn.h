#include "Unit.h"

class Pawn : public Unit
{
private:
	virtual char repr() const; // Actually `static` - indpendent of instance properties
public:
	Pawn(Position pos);

	// All overrides inherited methods from Unit:
	virtual vector<Position> pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const; // Throws exception if dest unreachable

	virtual bool enPassantOption(Position dest) const; // True on Pawn only if dest is in two squares from pos. Assuming valid move
	virtual bool canCommitEnPassant() const; // True on Pawn only
	virtual bool promotionAvaliable(int promotionRank) const; // True on Pawn only if on promotion rank
};
