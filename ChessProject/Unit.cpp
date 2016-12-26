#include "Unit.h"

Unit::Unit(Position pos) : _pos(pos)
{

}

Position Unit::getPos() const
{
	return _pos;
}

bool Unit::dangeringOneOf(vector<Position> positions, Direction playerDirection)
{
	bool isDangering = false;
	for (int i = 0; i < positions.size() & !isDangering; i++)
	{
		if (!pathToPosition(positions[i], true, playerDirection).empty())
		{
			isDangering = true;
		}
	}
	return isDangering;
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
	// Does nothing
}
