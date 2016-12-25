#include "Unit.h"

enum CastlingOption{None, Long, Short};

class Rook : Unit
{
private:
	bool moved;
	CastlingOption castlingOption;
public:
	Rook(Position pos, CastlingOption castlingOption);
	virtual ~Rook();

	// All inherited from Unit:
	virtual char repr() const; // Actually `static` - indpendent of instance properties
	virtual vector<Position> pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const; // Throws exception if dest unreachable
	virtual void move(Position dest); // No validation, just moves.

	virtual bool longCastlingAvaliable() const; // Returns false only if long castling Rook and moved
	virtual bool shortCastlingAvaliable() const; // Returns false only if short castling Rook and moved
};