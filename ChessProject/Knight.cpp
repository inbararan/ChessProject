#include "Knight.h"
#include "Exceptions.h"
#include <algorithm>
#pragma once

char Knight::repr() const
{
	return 'n';
}
Knight::Knight(const Position& pos) : Unit(pos)
{

}

// All overrides inherited methods from Unit:
// Throws exception if dest unreachable

vector<Position> Knight::pathToPosition(const Position& dest, MovementFlags& flags) const
 {
	flags = DEFAULT_FLAGS;
	if (!isReachable(dest))
	{
		flags.avaliability = Unreachable;
	}
	return vector<Position>();
}
bool Knight::isReachable(Position dest) const
{
	bool ans = false;
	if ((abs(dest.getFile() - _pos.getFile()) == 1 && abs(dest.getRank() - _pos.getRank()) == 2)
			|| (abs(dest.getFile() - _pos.getFile()) == 2 && abs(dest.getRank() - _pos.getRank()) == 1))
	{
		ans = true;
	}
	return ans;
}
