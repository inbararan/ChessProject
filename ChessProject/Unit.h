#pragma once

#include <string>

#include "Position.h"

using namespace std;

enum CastlingType{ None, Long, Short };

typedef struct MovementFlags
{
	CastlingType castling;
	bool enPassant;
} MovementFlags;

class Unit
{
protected:
	Position _pos;
	int _movesCount;

	virtual char repr() const = 0; // Lowercase, indpendent of instance properties
public:
	Unit(const Position& pos);

	const Position& getPos() const;

	char repr(bool toUpper) const; // Actually `static` - indpendent of instance properties
	virtual vector<Position> pathToPosition(const Position& dest, bool enemyThere) const; // Throws exception if dest unreachable
	virtual vector<Position> pathToPosition(const Position& dest, MovementFlags& flags, bool enemyThere) const = 0; // Throws exception if dest unreachable
	void move(const Position& dest); // No validation, just moves.
	void regretMove(const Position& src); // Decreases _movesCount instead of increasing it
	bool moved() const;

	virtual bool vital() const; // True for King only
	virtual bool canCommitEnPassant() const; // True on Pawn only
	virtual bool canPromote() const; // True on Pawn only
	virtual bool castlingRelevant(CastlingType castlingType, char& destFile) const; // For King and Rook only
};
