#pragma once

#include <string>

#include "Position.h"

using namespace std;

enum CastlingType{ None, Long, Short };

class Unit
{
protected:
	Position _pos;

	virtual char repr() const = 0; // Lowercase
public:
	Unit(Position pos);

	Position getPos() const; // Index in board repr

	virtual char repr(bool toUpper) const; // Actually `static` - indpendent of instance properties
	virtual vector<Position> pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const = 0; // Throws exception if dest unreachable
	virtual void move(Position dest); // No validation, just moves.
	virtual bool dangeringOneOf(vector<Position> positions, Direction playerDirection);

	virtual bool enPassantOption(Position dest) const; // True on Pawn only if dest is in two squares from pos. Assuming valid move
	virtual bool canCommitEnPassant() const; // True on Pawn only
	virtual bool promotionAvaliable(int promotionRank) const; // True on Pawn only if on promotion rank
	virtual bool castlingAvaliable(CastlingType castlingType) const; // Autmatically returns true if not King or matching Rook
	virtual CastlingType avaliableCastling(Position dest) const; // Returns Long or Short on King only if dest two squares to left or right from pos, else None
	virtual void commitCastling(CastlingType castlingType) const; // Does anything on King or Rook only
};
