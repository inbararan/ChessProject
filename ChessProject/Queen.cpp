#include "Queen.h"

// Actually `static` - indpendent of instance properties
char Queen::repr() const
{
	return 'q';
}

Queen::Queen(const Position& pos) : Unit(pos)
{

}

	// All overrides inherited methods from Unit:
vector<Position> Queen::pathToPosition(const Position& dest, MovementFlags& flags, bool enemyThere, Direction playerDirection) const
{
	vector<Position> positions;
	//is rook move
	if ((dest.getFile() == _pos.getFile() || dest.getRank() == _pos.getRank()))
	{
		Rook* r = new Rook(_pos);
		positions = r->pathToPosition(dest,flags,enemyThere,playerDirection);
		delete r;
	}
	//is bishop move
	else if ((abs(_pos.getFile() - dest.getFile()) == abs(_pos.getRank() - dest.getRank())))
	{
		Bishop* b = new Bishop(_pos);
		positions = b->pathToPosition(dest, flags, enemyThere, playerDirection);
		delete b;
	}
	else
	{
		throw UnreachablePositionException();
	}
	return positions;
}
// Throws exception if dest unreachable
