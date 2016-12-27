#include "Queen.h"

Queen::Queen(Position pos) : Unit(pos)
{

}

vector<Position> Queen::pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const
{
	// Actually Rook movement
	if (dest == _pos)
	{
		throw DestinationIsPositionException();
	}
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

char Queen::repr() const
{
	return 'q';
}
