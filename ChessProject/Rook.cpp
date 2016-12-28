#include "Rook.h"
#include "Position.h"
#include <iostream>
#include <algorithm>

char Rook::repr() const
{
	return 'r';
}

Rook::Rook(Position pos, CastlingType _castlingAvaliablity) : Unit(pos)
{
	this->_castlingAvaliablity = _castlingAvaliablity;
	_moved = false;
}

// All overrides inherited methods from Unit:
vector<Position> Rook::pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const
{
	int minRank, maxRank;
	char minFile, maxFile; 
	vector<Position> positions;
	if (dest.getFile() != _pos.getFile() && dest.getRank() != _pos.getRank())
	{
		throw UnreachablePositionException();
	}
	else
	{
		if (dest.getFile() == _pos.getFile())
		{
			minRank = min(dest.getRank(), _pos.getRank());
			maxRank = max(dest.getRank(), _pos.getRank());

			for (int i = minRank + 1; i < maxRank; i++)
			{
				Position p(_pos.getFile(),i);
				positions.push_back(p);
			}
		}
		else // the ranks are equal
		{
			minFile = min(dest.getFile(), _pos.getFile());
			maxFile = max(dest.getFile(), _pos.getFile());

			for (char i = minFile + 1; i < maxFile; i++)
			{
				Position p(i, _pos.getRank());
				positions.push_back(p);
			}
		}
	}
	return positions;
}

bool Rook::castlingAvaliable(CastlingType castlingType) const
{
	return _castlingAvaliablity == castlingType && !_moved;
}

void Rook::commitCastling(CastlingType castlingType) const
{

}