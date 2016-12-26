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

void Player::affect(string& board, bool toUpper) const
{
	for (int i = 0; i < _set.size(); i++)
	{
		board[_set[i]->posIndex()] = _set[i]->repr(toUpper);
	}
}

bool Player::longCastlingAvaliable() const
{
	bool avaliable = true;
	for (int i = 0; i < _set.size() && avaliable; i++)
	{
		if (!_set[i]->longCastlingAvaliable())
		{
			avaliable = false;
		}
	}
}

bool Player::shortCastlingAvaliable() const
{
	bool avaliable = true;
	for (int i = 0; i < _set.size() && avaliable; i++)
	{
		if (!_set[i]->shortCastlingAvaliable())
		{
			avaliable = false;
		}
	}
}
