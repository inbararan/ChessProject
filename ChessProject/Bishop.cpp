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
vector<Position> Bishop::pathToPosition(const Position& dest, MovementFlags& flags, bool enemyThere) const
{
	vector<Position> positions;

	if (abs(_pos.getFile() - dest.getFile()) == abs(_pos.getRank() - dest.getRank()))
	{
		if (_pos.getRank() < dest.getRank() && _pos.getFile() < dest.getFile())
		{
			for (int i = _pos.getRank() + 1, j = _pos.getFile() + 1; i < dest.getRank(), j < dest.getFile(); i++, j++)
			{
				positions.push_back(Position(j, i));
			}
		}
		else if (_pos.getRank() < dest.getRank() && _pos.getFile() > dest.getRank())
		{
			for (int i = _pos.getRank() + 1, j = _pos.getFile()  - 1; i < dest.getRank(), j > dest.getFile(); i++, j--)
			{
				positions.push_back(Position(j, i));
			}
		}
		else if (_pos.getRank() > dest.getRank() && _pos.getFile() < dest.getFile())
		{
			for (int i = _pos.getRank() -1 , j = _pos.getFile() + 1; i > dest.getRank(), j < dest.getFile(); i--, j++)
			{
				positions.push_back(Position(j, i));
			}
		}
		else
		{
			for (int i = _pos.getRank() - 1, j = _pos.getFile() - 1; i > dest.getRank(), j > dest.getFile(); i--, j--)
			{
				positions.push_back(Position(j, i));
			}
		}

		
	}
	else
	{
		throw UnreachablePositionException();
	}
	return positions;
}

