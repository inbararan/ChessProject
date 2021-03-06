#include "Rook.h"

char Rook::repr() const
{
	return 'r';
}

Rook::Rook(const Position& pos) : Unit(pos), _castlingAvaliablity(None)
{
}

Rook::Rook(const Position& pos, CastlingType castlingAvaliablity) : Unit(pos), _castlingAvaliablity(castlingAvaliablity)
{

}

// All overrides inherited methods from Unit:

vector<Position> Rook::pathToPosition(const Position& dest, MovementFlags& flags) const 
{
	vector<Position> positions;

	flags = DEFAULT_FLAGS;
	if (dest.getFile() != _pos.getFile() && dest.getRank() != _pos.getRank())
	{
		flags.avaliability = Unreachable;
	}
	else
	{
		if (dest.getFile() == _pos.getFile())
		{
			if (dest.getRank() < _pos.getRank())
			{
				for (int i = _pos.getRank() - 1; i > dest.getRank(); i--)
				{
					Position p(_pos.getFile(), i);
					positions.push_back(p);
				}
			}
			else
			{
				for (int i = _pos.getRank() + 1; i < dest.getRank(); i++)
				{
					Position p(_pos.getFile(), i);
					positions.push_back(p);
				}
			}
		}
		else // the ranks are equal
		{

			if (dest.getFile() <  _pos.getFile())
			{
				for (char i = _pos.getFile() - 1; i > dest.getFile(); i--)
				{
					Position p(i, _pos.getRank());
					positions.push_back(p);
				}
			}
			else
			{
				for (char i = _pos.getFile() + 1; i < dest.getFile(); i++)
				{
					Position p(i, _pos.getRank());
					positions.push_back(p);
				}
			}

			
		}
	}
	return positions;
}

bool Rook::castlingRelevant(CastlingType castlingType, char& destFile) const
{
	switch (castlingType)
	{
	case Long:
		destFile = _pos.getFile() - 3;
		break;
	case Short:
		destFile = _pos.getFile() + 2;
		break;
	default: // Shouldn't be called ever (castlingType == None)
		return false;
	}
	cout << !moved() << endl;
	cout << (castlingType == _castlingAvaliablity) << endl;
	return (castlingType == _castlingAvaliablity) && !moved();
}
