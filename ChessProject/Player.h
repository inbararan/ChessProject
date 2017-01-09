#pragma once

#include <string>
#include <algorithm>

#include "Unit.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

using namespace std;

class Player
{
private:
	vector<Unit*> _set;
	Direction _direction;
public:
	Player(Direction direction);
	Player(const Player& other);
	~Player();

	Direction getDirection() const;
	vector<Unit*> getSet() const;

	vector<Unit*> vitalUnits() const;
	bool hasUnitIn(const Position& pos) const;
	bool hasUnitsIn(vector<Position> positions) const; // Use for argument enemyThere in Unit::pathToMove
	Unit* getUnit(Position pos) const;
	void takeUnit(Unit* unit);
	void insertUnit(Unit* unit);
	void affect(string& board, bool toUpper) const;
};
