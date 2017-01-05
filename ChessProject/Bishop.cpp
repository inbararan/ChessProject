#include "Bishop.h"


char Bishop::repr() const
{
	return 'b';
}

Bishop::Bishop(const Position& pos) : Unit(pos)
{

}
Bishop::~Bishop()
{

}

// All overrides inherited methods from Unit:

// Throws exception if dest unreachable
vector<Position> Bishop::pathToPosition(const Position& dest, MovementFlags& flags, bool enemyThere, Direction playerDirection) const
{
	vector<Position> positions;
	char minFile,maxFile;
	int minRank, maxRank;

	if (abs(_pos.getFile() - _pos.getRank()) == abs(dest.getFile() - dest.getRank()))
	{
		minRank = min(_pos.getRank(), dest.getRank());
		maxRank = max(_pos.getRank(), dest.getRank());

		minFile = min(_pos.getFile(), dest.getFile());
		maxFile = max(_pos.getFile(), dest.getFile());

		for (int i = minRank,j = minFile; i < maxRank,j < maxFile; i++, j++)
		{
			positions.push_back(Position(i, j));
		}
	}
	else
	{
		throw UnreachablePositionException();
	}
	return positions;
}

