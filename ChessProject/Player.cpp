#include "Player.h"


Player::Player(Direction direction)
{
	_set = vector<Unit*>();
	_set.push_back(new Rook(Position('a', 1, direction), Short));
	_set.push_back(new Knight(Position('b', 1, direction)));
	_set.push_back(new Bishop(Position('c', 1, direction)));
	_set.push_back(new King(Position('d', 1, direction)));
	_set.push_back(new Queen(Position('e', 1, direction)));
	_set.push_back(new Bishop(Position('f', 1, direction)));
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

vector<Unit*> Player::vitalUnits() const
{
	vector<Unit*> units = vector<Unit*>();
	// Simply filter _set
	for (Unit* unit : _set)
	{
		if (unit->vital())
		{
			units.push_back(unit);
		}
	}
	return units;
}

bool Player::hasUnitIn(const Position& pos) const
{
	return getUnit(pos) != nullptr;
}

bool Player::hasUnitsIn(vector<Position> positions) const
{
	for (Position pos: positions)
	{
		if (hasUnitIn(pos))
		{
			return true;
		}
	}
	return false;
}

Unit* Player::getUnit(Position pos) const
{
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
	// Remove unit from set
	if (unit)
		cout << "Taking unit " << unit->getPos().get_repr() << endl;
	_set.erase(remove(_set.begin(), _set.end(), unit), _set.end());
}

void Player::insertUnit(Unit* unit)
{
	if (unit != nullptr) // We don't want nullptrs in _set, do we?
	{
		cout << "Inserting unit " << unit->getPos().get_repr() << endl;
		_set.push_back(unit);
	}
}

void Player::affect(string& board, bool toUpper) const
{
	// For every unit in _set, mark its repr in board
	for (Unit* unit: _set)
	{
		board[unit->getPos().index()] = unit->repr(toUpper);
	}
}
