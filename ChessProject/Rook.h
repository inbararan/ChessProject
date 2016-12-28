#include "Unit.h"

class Rook : public Unit
{
private:
	CastlingType _castlingAvaliablity;
	virtual char repr() const; // Actually `static` - indpendent of instance properties
public:
	Rook(Position pos, CastlingType _castlingAvaliablity);

	// All overrides inherited methods from Unit:
	virtual vector<Position> pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const; // Throws exception if dest unreachable

	virtual bool castlingAvaliable(CastlingType castlingType) const;
	virtual bool longCastlingAvaliable() const; // Returns false only if long castling Rook and moved
	virtual bool shortCastlingAvaliable() const; // Returns false only if short castling Rook and moved
	virtual void commitCastling(CastlingType castlingType) const; // Does anything only if castlingType fits _castlingAvaliablity
};
