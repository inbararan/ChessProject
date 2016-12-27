#include "Unit.h"

Unit::Unit(Position pos) : _pos(pos), _moved(false)
{

}

Position Unit::getPos() const
{
	return _pos;
}

void Unit::move(Position dest)
{
	_pos = Position(dest);
	_moved = true;
}

bool Unit::dangeringOneOf(vector<Position> positions, Direction playerDirection)
{
	bool dangering = false;
	for (int i = 0; i < positions.size() && !dangering; i++)
	{
		try
		{
			pathToPosition(positions[i], true, playerDirection);
			dangering = true;
		}
		catch (UnreachablePositionException e)
		{
			// positions[i] is not takeable by *this
		}
	}
	return dangering;
}

bool Unit::dangeringOneOf(vector<Unit*> units, Direction playerDirection)
{
	bool dangering = false;
	for (int i = 0; i < units.size() && !dangering; i++)
	{
		try
		{
			pathToPosition(units[i]->getPos(), true, playerDirection);
			dangering = true;
		}
		catch (UnreachablePositionException e)
		{
			// units[i] is not takeable by *this
		}
	}
	return dangering;
}

char Unit::repr(bool toUpper) const
{
	return toUpper ? toupper(repr()) : tolower(repr());
}

bool Unit::enPassantOption(Position dest) const
{
	return false;
}

bool Unit::canCommitEnPassant() const
{
	return false;
}

bool Unit::promotionAvaliable(int promotionRank) const
{
	return false;
}

bool Unit::castlingAvaliable(CastlingType castlingType) const
{
	return false;
}
CastlingType Unit::avaliableCastling(Position dest) const
{
	return None;
}

void Unit::commitCastling(CastlingType castlingType) const
{
	// Supposed to do nothing
}

bool Unit::vital() const
{
	return false;
}
