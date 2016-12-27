#include "Queen.h"

char Queen::repr() const
{
	return 'q';
}

Queen::Queen(Position pos) : Unit(pos)
{

}

vector<Position> Queen::pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const
{
	// Actually Rook movement
	if (dest.sameFile(_pos))
	{
		return Position::positionsRangeOnFile(_pos.getFile(), dest.getRank(), _pos.getRank());
	}
	else if (dest.sameRank(_pos))
	{
		return Position::positionsRangeOnRank(_pos.getRank(), dest.getFile(), _pos.getFile());
	}
	else
	{
		throw UnreachablePositionException();
	}
}
