#pragma once

#include <string>
#include <algorithm>

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
	void takeUnit(Position pos);
	void takeUnit(Unit* unit);
	void affect(string& board, bool toUpper) const;
	
	CastlingType avaliableCastling(Position dest) const; // Extracts from King the avaliable castling type
	bool castlingAvaliable(CastlingType castlingType) const;

	void commitCastling(CastlingType castlingType);
};
