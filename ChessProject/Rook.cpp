#include "Rook.h"
#include "Position.h"
#include <iostream>

using namespace std;

char Rook::repr() const
{
	return 'r';
}

Rook::Rook(Position pos, CastlingType _castlingAvaliablity) : Unit(pos)
{
	this->_castlingAvaliablity = _castlingAvaliablity;
	_moved = false;
}

// All overrides inherited methods from Unit:
vector<Position> Rook::pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const
{
	return vector<Position>();
}

bool Rook::castlingAvaliable(CastlingType castlingType) const
{
	return true;
}

// Does anything only if castlingType fits _castlingAvaliablity
void Rook::commitCastling(CastlingType castlingType) const
{

}
