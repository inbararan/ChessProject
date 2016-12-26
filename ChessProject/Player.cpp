#include "Player.h"

int getAbsoluteRank(int relativeRank, Direction userDirection)
{
	switch (userDirection)
	{
	case Up:
		return relativeRank;
	case Down:
		return MAX_RANK - relativeRank;
	}
}

Player::Player(Direction direction)
{
	_set = vector<Unit*>();
	_set.push_back(new Queen(Position('d', getAbsoluteRank(1, direction))));
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
vector<Unit*> Player::unitsIn(vector<Position> positions) const
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
	return units;
}

vector<Unit*> Player::unitsDangering(vector<Position> positions) const
{
	vector<Unit*> units = vector<Unit*>();
	for (int i = 0; i < _set.size(); i++)
	{
		if (_set[i]->dangeringOneOf(positions, _direction))
		{
			units.push_back(_set[i]);
		}
	}
	return units;
}

Unit* Player::getUnit(Position pos) const
{
	Unit* unit = nullptr;
	for (int i = 0; i < _set.size() && unit == nullptr; i++)
	{
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
	_set.erase(remove(_set.begin(), _set.end(), unit), _set.end());
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
}

void Player::commitCastling(CastlingType castlingType)
{
	for (int i = 0; i < _set.size(); i++)
	{
		_set[i]->commitCastling(castlingType);
	}
}