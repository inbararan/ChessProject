#include "Game.h"

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
		// Find source Unit
		Unit* unit = currentPlayer().getUnit(src);
		// Check src and dst
		if (unit == nullptr) // Current player has no units in src
		{
			return SRC_NOT_OCUUPIED;
		}
		if (currentPlayer().getUnit(dst) != nullptr)
		{
			return DST_OCCUPIED;
		}
		// Check if src can move to dst
		vector<Position> path = unit->pathToPosition(dst, currentOpponent().getUnit(dst) != nullptr, currentPlayer().getDirection());
		if (currentPlayer().unitsIn(path).empty() && currentOpponent().unitsIn(path).empty())
		{
			unit->move(dst);
			currentOpponent().takeUnit(dst);
			_currentPlayerIndicator = !_currentPlayerIndicator;
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
	catch (DestinationIsPositionException e)
	{
		return DST_EQL_SRC;
	}
	return isCheckTo(!_currentPlayerIndicator) ? CHECK : OK;
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

Player& Game::currentPlayer()
{
	return _currentPlayerIndicator ? _player1 : _player2;
}

Player& Game::currentOpponent()
{
	return _currentPlayerIndicator ? _player2 : _player1;
}

bool Game::isCheckTo(bool currentPlayer)
{
	//TODO
	return false;
}

bool Game::isCheckmateTo(bool currentPlayer)
{
	//TODO
	return false;
}
