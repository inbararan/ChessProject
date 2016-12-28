#include "Player.h"


Player::Player(Direction direction)
{
	_set = vector<Unit*>();
	_set.push_back(new King(Position('c', 1, direction)));
	_set.push_back(new Queen(Position('a', 1, direction)));
	_set.push_back(new Queen(Position('b', 2, direction)));
	_set.push_back(new Queen(Position('g', 2, direction)));
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
	for (Position pos: positions)
	{
		if (getUnit(pos) != nullptr)
		{
			return true;
		}
	}
	return false;
}

vector<Unit*> Player::vitalUnits() const
{
	vector<Unit*> units = vector<Unit*>();
	for (Unit* unit: _set)
	{
		if (unit->vital())
		{
			units.push_back(unit);
		}
	}
	return units;
}

Unit* Player::getUnit(Position pos) const
{
	cout << "Getting unit in " << pos.getFile() << pos.getRank() << endl;
	for (Unit* unit: _set)
	{
		if (unit->getPos() == pos)
		{
			return unit;
		}
	}
	return nullptr;
}

void Player::takeUnit(Unit* unit)
{
	if (unit)
		cout << "Taking unit: " << unit->getPos().getFile() << unit->getPos().getFile() << endl;
	cout << "Before: " << _set.size() << endl;
	_set.erase(remove(_set.begin(), _set.end(), unit), _set.end());
	cout << "After:  " << _set.size() << endl << endl;
}

void Player::insertUnit(Unit* unit)
{
	_set.push_back(unit);
}

void Player::affect(string& board, bool toUpper) const
{
	for (Unit* unit: _set)
	{
		board[unit->getPos().index()] = unit->repr(toUpper);
	}
}

CastlingType Player::avaliableCastling(Position dest) const
{
	for (Unit* unit : _set)
	{
		CastlingType avaliable = unit->avaliableCastling(dest);
		if (avaliable != None)
		{
			return avaliable;
		}
	}
	return None;
}

bool Player::castlingAvaliable(CastlingType castlingType) const
{
	for (Unit* unit : _set)
	{
		if (!unit->castlingAvaliable(castlingType))
		{
			return false;
		}
	}
	return true;
}

void Player::commitCastling(CastlingType castlingType)
{
	for (Unit* unit : _set)
	{
		unit->commitCastling(castlingType);
	}
}
