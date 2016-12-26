#include "Unit.h"

Unit::Unit(Position pos) : _pos(pos)
{

}

int Unit::posIndex() const
{
	return _pos.index();
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

bool Unit::longCastlingAvaliable() const
{
	return false;
}

bool Unit::shortCastlingAvaliable() const
{
	return false;
}

CastlingType Unit::avaliableCastling(Position dest) const
{
	return None;
}

void Unit::commitCastling(CastlingType castlingType) const
{

}
