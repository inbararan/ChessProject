#include "Unit.h"

Unit::Unit(const Position& pos) : _pos(Position(pos)), _moved(false)
{

}

const Position& Unit::getPos() const
{
	return _pos;
}

void Unit::move(const Position& dest)
{
	_pos = Position(dest);
	_moved = true;
}

char Unit::repr(bool toUpper) const
{
	return toUpper ? toupper(repr()) : tolower(repr());
}

bool Unit::canCommitEnPassant() const
{
	return false;
}

bool Unit::vital() const
{
	return false;
}
