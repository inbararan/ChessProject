#include "Game.h"

Game::Game() : player1(Player(Up)), player2(Player(Down))
{
	currentPlayerIndicator = WHITE;
	enPassantDetails.isSet = false;
}

Game::Game(const Game& other) : player1(Player(other.player1)), player2(Player(other.player2))
{
	currentPlayerIndicator = other.currentPlayerIndicator;
	enPassantDetails = other.enPassantDetails;
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
	char board[BOARD_SIZE][BOARD_SIZE] = { 0 };
	player1.affect(board, true); // White
	player2.affect(board, false); // Black
	repr += currentPlayerIndicator ? '0' : '1';
	return repr;
}

Player& Game::currentPlayer()
{
	return currentPlayerIndicator ? player1 : player2;
}

Player& Game::currentOpponent()
{
	return currentPlayerIndicator ? player2 : player1;
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
