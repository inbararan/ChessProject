#include "King.h"

char King::repr() const
{
	return 'k';
}

King::King(const Position& pos) : Unit(pos)
{

}

vector<Position> King::pathToPosition(const Position& dest, MovementFlags& flags, bool enemyThere, Direction playerDirection) const
{
	if (abs(dest.getFile() - _pos.getFile()) > 1 || abs(dest.getRank() - _pos.getRank()) > 1)
	{
		throw UnreachablePositionException();
	}
	return vector<Position>();
}

bool King::vital() const
{
	return true;
}
