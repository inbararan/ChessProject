#include "Unit.h"

Unit::Unit(const Position& pos) : _pos(Position(pos)), _movesCount(0)
{

}

const Position& Unit::getPos() const
{
	return _pos;
}

void Unit::move(const Position& dest)
{
	_pos = Position(dest);
	_movesCount++;
}

void Unit::regretMove(const Position& src)
{
	_pos = Position(src);
	_movesCount--;
}

bool Unit::moved() const
{
	return _movesCount != 0;
}

char Unit::repr(bool toUpper) const
{
	// According to protocol with fronted, unit color affects case
	return toUpper ? toupper(repr()) : tolower(repr());
}

bool Unit::vital() const
{
	return false;
}

bool Unit::canPromote() const
{
	return false;
}

bool Unit::castlingRelevant(CastlingType castlingType, char& destFile) const
{
	return false;
}
