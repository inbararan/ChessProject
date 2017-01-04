#include "Exceptions.h"
#include "Bishop.h"
#include <algorithm>


char Bishop::repr() const
{
	return 'b';
}

Bishop::Bishop(Position pos) : Unit(pos)
{

}
Bishop::~Bishop()
{

}

// All overrides inherited methods from Unit:

// Throws exception if dest unreachable
vector<Position> Bishop::pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const
{
	vector<Position> positions;
	char minFile,maxFile;
	int minRank, maxRank;

	if ((dest.getFile() > 'h' || dest.getFile() < 'a') && (dest.getRank() < 1 || dest.getRank() > 8))
	{
		throw OutOfBoardException();
		return positions;
	}
	else
	{
		if (abs(_pos.getFile() - _pos.getRank()) == abs(dest.getFile() - dest.getRank()))
		{
			minRank = min(_pos.getRank(), dest.getRank());
			maxRank = max(_pos.getRank(), dest.getRank());

			minFile = min(_pos.getFile(), dest.getFile());
			maxFile = max(_pos.getFile(), dest.getFile());

			for (int i = minRank,j = minFile; i < maxRank,j < maxFile; i++)
			{
				Position p(i, j);
				positions.push_back(p);
			}
		}
		else
		{
			throw UnreachablePositionException();
			return positions;
		}
	}
	return positions;
}

