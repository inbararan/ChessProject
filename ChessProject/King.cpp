#include "King.h"

char King::repr() const
{
	return 'k';
}

King::King(const Position& pos) : Unit(pos)
{

}

vector<Position> King::pathToPosition(const Position& dest, MovementFlags& flags, bool enemyThere) const
{
	vector<Position> path = vector<Position>();
	if (abs(dest.getFile() - _pos.getFile()) > 1 || abs(dest.getRank() - _pos.getRank()) > 1)
	{
		if (!enemyThere && dest.sameRank(_pos) && dest.getFile() - _pos.getFile() == 2)
		{
			flags.castling = Long;
			path.push_back(Position(_pos.getFile() + 1, _pos.getRank()));
		}
		else if (!enemyThere && dest.sameRank(_pos) && dest.getFile() - _pos.getFile() == -2)
		{
			flags.castling = Short;
			path.push_back(Position(_pos.getFile() - 1, _pos.getRank()));
		}
		else
		{
			throw UnreachablePositionException();
		}
	}
	return path;
}

bool King::vital() const
{
	return true;
}

bool King::castlingRelevant(CastlingType castlingType, char& destFile) const
{
	switch (castlingType)
	{
	case Long:
		destFile = _pos.getFile() + 2;
		break;
	case Short:
		destFile = _pos.getFile() - 2;
		break;
	default: // Shouldn't be called ever (castlingType == None)
		return false;
	}
	return !moved();
}
