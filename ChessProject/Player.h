#pragma once

#include <string>

#include "Unit.h"

using namespace std;

#define UNITS_NUM 16

class Player
{
private:
	Unit* set[UNITS_NUM]; // King is always in set[0]
	Direction direction;

public:
	Player(Direction direction);
	~Player();

	vector<Unit*> unitsIn(vector<Position> positions) const; // Use for argument enemyThere in Unit::pathToMove
	vector<Unit*> unitsDangering(vector<Position> positions) const; // Use in check and castling
	Unit* getUnit(Position pos) const;

	bool longCastlingAvaliable() const;
	bool shortCastlingAvaliable() const;

	void commitLongCastling();
	void commitShortCastling();
};
