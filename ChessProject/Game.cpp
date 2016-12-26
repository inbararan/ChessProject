#include "Game.h"

Game::Game() : _player1(Player(Up)), _player2(Player(Down))
{
	_currentPlayerIndicator = WHITE;
	_enPassantDetails.isSet = false;
}

Game::Game(const Game& other) : _player1(Player(other._player1)), _player2(Player(other._player2))
{
	_currentPlayerIndicator = other._currentPlayerIndicator;
	_enPassantDetails = other._enPassantDetails;
}

Game::~Game()
{
	
}

string Game::nextMove(string moveRepr)
{
	//TODO
	return "00";
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

bool isCheckTo(bool currentPlayer)
{
	//TODO
	return false;
}

bool isCheckmateTo(bool currentPlayer)
{
	//TODO
	return false;
}
