#include "Pawn.h"

char Pawn::repr() const
{
	return 'p';
}

Pawn::Pawn(const Position& pos) : Unit(pos)
{
}

vector<Position> Pawn::pathToPosition(const Position& dest, MovementFlags& flags) const
{
	flags = DEFAULT_FLAGS;
	vector<Position> path = vector<Position>();
	switch (abs(_pos.getFile() - dest.getFile()))
	{
	case 0:
		flags.avaliability = Regular;
		break;
	case 1:
		flags.avaliability = Capture;
		break;
	default:
		flags.avaliability = Unreachable;
		return path;
		break;
	}
	switch (_pos.getRank() - dest.getRank())
	{
	case -2:
		if (!moved() && flags.avaliability == Regular)
		{
			flags.enPassantTarget = true;
			flags.moveDirection = Up;
		}
		else
		{
			flags.avaliability = Unreachable;
		}
		break;
	case -1:
		flags.moveDirection = Up;
		break;
	case 1:
		flags.moveDirection = Down;
		break;
	case 2:
		if (!moved() && flags.avaliability == Regular)
		{
			flags.enPassantTarget = true;
			flags.moveDirection = Down;
		}
		else
		{
			flags.avaliability = Unreachable;
		}
		break;
	default:
		flags.avaliability = Unreachable;
	}
	return path;
}

bool Pawn::canPromote() const
{
	return true;
}
