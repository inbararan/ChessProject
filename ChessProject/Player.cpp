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
	for (int i = 0; i < _set.size(); i++)
	{
		delete _set[i];
	}
}

Direction Player::getDirection() const
{
	return _direction;
}

bool Player::hasUnitsIn(vector<Position> positions) const
{
	vector<Unit*> units = vector<Unit*>();
	for (int i = 0; i < positions.size(); i++)
	{
		Unit* unit = getUnit(positions[i]);
		if (unit != nullptr)
		{
			units.push_back(unit);
		}
	}
	return !units.empty();
}

bool Player::isDangeringOneOf(vector<Position> positions) const
{
	vector<Unit*> units = vector<Unit*>();
	for (int i = 0; i < _set.size(); i++)
	{
		if (_set[i]->dangeringOneOf(positions, _direction))
		{
			units.push_back(_set[i]);
		}
	}
	return !units.empty();
}

bool Player::isDangeringOneOf(vector<Unit*> units) const
{
	vector<Unit*> dangeringUnits = vector<Unit*>();
	for (int i = 0; i < _set.size(); i++)
	{
		if (_set[i]->dangeringOneOf(units, _direction))
		{
			dangeringUnits.push_back(_set[i]);
		}
	}
	return !dangeringUnits.empty();
}

vector<Unit*> Player::vitalUnits() const
{
	vector<Unit*> units = vector<Unit*>();
	for (int i = 0; i < _set.size(); i++)
	{
		if (_set[i]->vital())
		{
			units.push_back(_set[i]);
		}
	}
	return units;
}

Unit* Player::getUnit(Position pos) const
{
	Unit* unit = nullptr;
	cout << "pos:" << pos.getFile() << pos.getRank() << endl;
	for (int i = 0; i < _set.size() && unit == nullptr; i++)
	{
		cout << i << ":" << _set[i]->getPos().getFile() << _set[i]->getPos().getRank() << endl;
		if (_set[i]->getPos() == pos)
		{
			unit = _set[i];
		}
	}
	return unit;
}

void Player::takeUnit(Position pos)
{
	takeUnit(getUnit(pos));
}

void Player::takeUnit(Unit* unit)
{
	if (unit != nullptr)
	{
		_set.erase(remove(_set.begin(), _set.end(), unit), _set.end());
	}
}

void Player::affect(string& board, bool toUpper) const
{
	for (int i = 0; i < _set.size(); i++)
	{
		board[_set[i]->getPos().index()] = _set[i]->repr(toUpper);
	}
}

CastlingType Player::avaliableCastling(Position dest) const
{
	CastlingType avaliable = None;
	for (int i = 0; i < _set.size() && avaliable == None; i++)
	{
		avaliable = _set[i]->avaliableCastling(dest);
	}
	return avaliable;
}

bool Player::castlingAvaliable(CastlingType castlingType) const
{
	bool avaliable = true;
	for (int i = 0; i < _set.size() && avaliable; i++)
	{
		if (!_set[i]->castlingAvaliable(castlingType))
		{
			avaliable = false;
		}
	}
	return avaliable;
}

void Player::commitCastling(CastlingType castlingType)
{
	for (int i = 0; i < _set.size(); i++)
	{
		_set[i]->commitCastling(castlingType);
	}
}
