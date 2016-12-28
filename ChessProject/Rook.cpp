#include "Rook.h"
#include "Position.h"
#include <iostream>

using namespace std;

Rook::Rook(Position pos, CastlingType _castlingAvaliablity) : Unit(pos)
{
	this->_castlingAvaliablity = _castlingAvaliablity;
}

// All overrides inherited methods from Unit:
vector<Position> Rook::pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const
{

}
// Returns false only if long castling Rook and moved
bool Rook::longCastlingAvaliable() const
{
	bool ans;
	switch (this->_castlingAvaliablity)
	{
	case None:
	case Short:
		ans = false;
		break;
	case Long:
		ans = true;
		break;
	}
	return ans;
}
// Returns false only if short castling Rook and moved
bool Rook::shortCastlingAvaliable() const
{

}
// Does anything only if castlingType fits _castlingAvaliablity
void Rook::commitCastling(CastlingType castlingType) const
{

}