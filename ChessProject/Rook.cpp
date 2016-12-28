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
	return longCastlingAvaliable() || shortCastlingAvaliable();
}
// Returns false only if long castling Rook and moved
bool Rook::longCastlingAvaliable() const
{
	return (this->_castlingAvaliablity == Long) && !_moved;
}
// Returns false only if short castling Rook and moved
bool Rook::shortCastlingAvaliable() const
{
	return (this->_castlingAvaliablity == Short) && !_moved;
}
// Does anything only if castlingType fits _castlingAvaliablity
void Rook::commitCastling(CastlingType castlingType) const
{

}