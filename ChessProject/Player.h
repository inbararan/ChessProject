#pragma once

#include <string>

#include "Unit.h"
#include "Queen.h"

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

	vector<Unit*> unitsIn(vector<Position> positions) const; // Use for argument enemyThere in Unit::pathToMove
	vector<Unit*> unitsDangering(vector<Position> positions) const; // Use in check and castling
	Unit* getUnit(Position pos) const;
	void takeUnit(Unit* unit);
	void affect(string& board, bool toUpper) const;

	bool longCastlingAvaliable() const;
	bool shortCastlingAvaliable() const;

	void commitLongCastling();
	void commitShortCastling();
};
