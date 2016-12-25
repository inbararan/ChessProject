#pragma once

#include <string>
#include <vector>

#include "Position.h"

using namespace std;

class Unit
{
private:
	Position pos;
	bool moved;
public:
	Unit(Position pos);
	virtual ~Unit();

	virtual char repr() const = 0; // Actually `static` - indpendent of instance properties
	virtual vector<Position> pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const = 0; // Throws exception if dest unreachable
	virtual void move(Position dest) = 0; // No validation, just moves.
	virtual bool dangers(Position dest) = 0; // For Player::unitsDangering

	virtual bool enPassantOption(Position dest); // True on Pawn only if dest is in o squares from pos. Assuming valid move

	virtual bool canCommitEnPassant() const; // True on Pawn only
	virtual bool isEnPassantMove(Position dest) const; // True on Pawn only if dest is in two squares move assuming move is legal
	virtual bool promotionAvaliable(int promotionRow) const; // True on Pawn only if on promotion row
	virtual bool longCastlingAvaliable() const; // Autmatically returns true if not King or big Rook
	virtual bool shortCastlingAvaliable() const; // Autmatically returns true if not King or small Rook
};
