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
