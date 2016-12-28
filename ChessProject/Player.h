#pragma once

#include <string>
#include <algorithm>

#include "Unit.h"
#include "Queen.h"
#include "King.h"
#include "Rook.h"

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

	bool hasUnitsIn(vector<Position> positions) const; // Use for argument enemyThere in Unit::pathToMove
	vector<Unit*> vitalUnits() const;
	Unit* getUnit(Position pos) const;
	void takeUnit(Unit* unit);
	void insertUnit(Unit* unit);
	void affect(string& board, bool toUpper) const;
	
	CastlingType avaliableCastling(Position dest) const; // Extracts from King the avaliable castling type
	bool castlingAvaliable(CastlingType castlingType) const;

	void commitCastling(CastlingType castlingType);
};
