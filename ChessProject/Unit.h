#pragma once

#include <string>
#include <vector>

#include "Position.h"

using namespace std;

enum CastlingType{ None, Long, Short };

class Unit
{
protected:
	Position _pos;

	virtual char repr() const; // Lowercase
public:
	Unit(Position pos);

	int posIndex() const; // Index in board repr

	virtual char repr(bool toUpper) const; // Actually `static` - indpendent of instance properties
	virtual vector<Position> pathToPosition(Position dest, bool enemyThere, Direction playerDirection) const = 0; // Throws exception if dest unreachable
	virtual void move(Position dest) = 0; // No validation, just moves.

	virtual bool enPassantOption(Position dest) const; // True on Pawn only if dest is in two squares from pos. Assuming valid move
	virtual bool canCommitEnPassant() const; // True on Pawn only
	virtual bool promotionAvaliable(int promotionRank) const; // True on Pawn only if on promotion rank
	virtual bool longCastlingAvaliable() const; // Autmatically returns true if not King or long castling Rook
	virtual bool shortCastlingAvaliable() const; // Autmatically returns true if not King or short castling Rook
	virtual CastlingType avaliableCastling(Position dest) const; // Returns Long or Short if dest two squares to left or right from pos, else None
	virtual void commitCastling(CastlingType castlingType) const; // Does anything on King or Rook only
};
