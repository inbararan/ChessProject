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
	// According to protocol with fronted, unit color affects case
	return toUpper ? toupper(repr()) : tolower(repr());
}

vector<Position> Unit::pathToPosition(const Position& dest, bool enemyThere, Direction playerDirection) const
{
	MovementFlags unnessecaryFlags = { 0 };
	return pathToPosition(dest, unnessecaryFlags, enemyThere, playerDirection);
}

bool Unit::isCastlingAvaliable(CastlingType castlingType) const
{
	return true;
}

bool Unit::canCommitEnPassant() const
{
	return false;
}

bool Unit::vital() const
{
	return false;
}
