#include "Player.h"


Player::Player(Direction direction)
{
	_set = vector<Unit*>();
	_set.push_back(new Rook(Position('a', 1, direction), Short));
	_set.push_back(new Knight(Position('b', 1, direction)));
	//_set.push_back(new Bishop(Position('c', 1, direction)));
	_set.push_back(new King(Position('d', 1, direction)));
	//_set.push_back(new Bishop(Position('f', 1, direction)));
	_set.push_back(new Knight(Position('g', 1, direction)));
	_set.push_back(new Rook(Position('h', 1, direction), Long));
	_direction = direction;
}
/*
Player::Player(const Player& other)
{
	set = vector<Unit*>();
	for (int i = 0; i < other.set.size(); i++)
	{
		set.push_back(nullptr);
	}
	direction = other.direction;
}
*/
Player::~Player()
{
	// Delete all units
	for (Unit* unit: _set)
	{
		delete unit;
	}
}

Direction Player::getDirection() const
{
	return _direction;
}

vector<Unit*> Player::getSet() const
{
	return _set;
}

bool Player::hasUnitsIn(vector<Position> positions) const
{
	// Check for every position if it is the position of one of player's units
	for (Position pos: positions)
	{
		if (getUnit(pos) != nullptr)
		{
			return true;
		}
	}
	// If no such position found, return false
	return false;
}

vector<Unit*> Player::vitalUnits() const
{
	vector<Unit*> units = vector<Unit*>();
	// Collect units that are vital from _set
	for (Unit* unit: _set)
	{
		if (unit->vital())
		{
			units.push_back(unit);
		}
	}
	// Return collected units
	return units;
}

Unit* Player::getUnit(Position pos) const
{
	// Find unit in _set that has position equal to pos
	for (Unit* unit: _set)
	{
		if (unit->getPos() == pos)
		{
			return unit;
		}
	}
	// If no unit was found return nullptr
	return nullptr;
}

void Player::takeUnit(Unit* unit)
{
	// Remove unit from set
	_set.erase(remove(_set.begin(), _set.end(), unit), _set.end());
}

void Player::insertUnit(Unit* unit)
{
	if (unit != nullptr) // We don't want nullptrs in _set, do we?
	{
		_set.push_back(unit);
	}
}

void Player::affect(string& board, bool toUpper) const
{
	// Mark player's units in board, uppercased if needed
	for (Unit* unit: _set)
	{
		// In appropriate index in board, set unit's repr, uppercased if needed
		board[unit->getPos().index()] = unit->repr(toUpper);
	}
}

/*CastlingType Player::avaliableCastling(Position dest) const
{
	// Iterate over all units
	for (Unit* unit : _set)
	{
		// All units but King returns None because they have nothing to do with castling (Castling is a King move)
		CastlingType avaliable = unit->avaliableCastling(dest);
		if (avaliable != None)
		{
			// King returns castling type according to dest
			return avaliable;
		}
	}
	// If even the King returned None it means the move isn't castling so return None
	return None;
}

bool Player::castlingAvaliable(CastlingType castlingType) const
{
	// Ask all units if castling is avaliable
	for (Unit* unit : _set)
	{
		// If one refuses than castling isn't avaliable
		if (!unit->castlingAvaliable(castlingType))
		{
			return false;
		}
	}
	// If all units agree that castling is avaliable (not even one refused) - it's avaliable
	return true;
}

void Player::commitCastling(CastlingType castlingType)
{
	// Tell all the units to commit castling (Most won't do anything about it)
	for (Unit* unit : _set)
	{
		unit->commitCastling(castlingType);
	}
}
*/