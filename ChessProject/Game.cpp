#include "Game.h"

Player& Game::getPlayer(bool playerIndicator)
{
	return playerIndicator ? _player1 : _player2;
}

bool Game::isCheckTo(bool playerIndicator)
{
	// For every player's vital unit, check if in danger:
	// For every opponent units, check if path to vital unit existing and clean
	vector<Unit*> vitals = getPlayer(playerIndicator).vitalUnits();
	vector<Unit*> opponentUnits = getPlayer(!playerIndicator).getSet();
	for (Unit* vital : vitals)
	{
		for (Unit* opponentUnit : opponentUnits)
		{
			try
			{
				if (isClean(opponentUnit->pathToPosition(vital->getPos(), true, getPlayer(OPPONENT).getDirection())))
				{
					return true;
				}
			}
			catch (UnreachablePositionException e)
			{
				// vital unrachable by opponentUnit, thats all
			}
		}
	}
	return false;
}

bool Game::isCheckmateTo(bool playerIndicator)
{
	//TODO
	return false;
}

bool Game::isClean(vector<Position> path)
{
	return !getPlayer(PLAYER).hasUnitsIn(path) && !getPlayer(OPPONENT).hasUnitsIn(path);
}

void Game::regret(Move move)
{
	move.moved->move(move.dest);
	getPlayer(OPPONENT).insertUnit(move.taken);
}

Game::Game() : _player1(Player(Up)), _player2(Player(Down))
{
	_currentPlayerIndicator = WHITE;
	_enPassantDetails.isSet = false;
}
/*
Game::Game(const Game& other) : _player1(Player(other._player1)), _player2(Player(other._player2))
{
	_currentPlayerIndicator = other._currentPlayerIndicator;
	_enPassantDetails = other._enPassantDetails;
}
*/
string Game::nextMove(string moveRepr)
{
	try
	{
		// First, parse moveRepr
		Position src = Position(moveRepr.substr(0, 2));
		Position dst = Position(moveRepr.substr(2, 2));
		// Make sure there is an actual MOVEMENT trial
		if (src == dst)
		{
			return DST_EQL_SRC;
		}
		// Find source Unit
		Unit* unit = getPlayer(PLAYER).getUnit(src);
		// Check src and dst
		if (unit == nullptr) // Current player has no units in src
		{
			return SRC_NOT_OCUUPIED;
		}
		if (getPlayer(PLAYER).getUnit(dst) != nullptr)
		{
			return DST_OCCUPIED;
		}
		// Check if src can move to dst
		vector<Position> path = unit->pathToPosition(dst, getPlayer(OPPONENT).getUnit(dst) != nullptr, getPlayer(PLAYER).getDirection());
		if (isClean(path))
		{
			Move move = { unit, Position(dst), getPlayer(OPPONENT).getUnit(dst) };
			unit->move(dst);
			getPlayer(OPPONENT).takeUnit(move.taken);
			/*if (isCheckTo(PLAYER))
			{
				delete move.taken;
			}
			else
			{
				regret(move);
				return MOVE_CAUSES_SELF_CHECK;
			}*/
		}
		else
		{
			return ILLEGAL_MOVEMENT; // ?
		}
	}
	catch (OutOfBoardException e)
	{
		return OUT_OF_BORDER;
	}
	catch (UnreachablePositionException e)
	{
		return ILLEGAL_MOVEMENT;
	}
	string status = isCheckTo(OPPONENT) ? CHECK : OK;
	_currentPlayerIndicator = !_currentPlayerIndicator;
	return status;
}

string Game::getBoardRepr() const
{
	string repr = "";
	repr.assign(64, '#');
	_player1.affect(repr, true); // White
	_player2.affect(repr, false); // Black
	repr += _currentPlayerIndicator ? '0' : '1';
	return repr;
}
