#include "Game.h"

Player& Game::getPlayer(bool playerIndicator)
{
	return playerIndicator ? _player1 : _player2;
}

Move Game::commitMove(Unit* toMove, Position dest, Player& opponent)
{
	Move move = { toMove, toMove->getPos(), opponent.getUnit(dest) };
	toMove->move(dest);
	opponent.takeUnit(move.taken);
	return move;
}

bool Game::isCheckTo(bool playerIndicator)
{
	vector<Unit*> vitals = getPlayer(playerIndicator).vitalUnits();
	vector<Unit*> opponentUnits = getPlayer(!playerIndicator).getSet();
	for (Unit* vital : vitals)
	{
		for (Unit* opponentUnit : opponentUnits)
		{
			try
			{
				if (isClear(opponentUnit->pathToPosition(vital->getPos(), true, getPlayer(!playerIndicator).getDirection())))
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

bool Game::isCheckmate()
{
	for (Unit* optionalSaver : getPlayer(OPPONENT).getSet())
	{
		for (Position pos : Position::allPossiblePositions())
		{
			vector<Position> path = vector<Position>();
			try
			{
				path = optionalSaver->pathToPosition(pos, getPlayer(CURRENT).getUnit(pos) != nullptr, getPlayer(OPPONENT).getDirection());
			}
			catch (UnreachablePositionException e)
			{
				// pos unreachable by optionalSaver
			}
			if (isClear(path))
			{
				Move move = commitMove(optionalSaver, pos, getPlayer(CURRENT));
				bool check = isCheckTo(OPPONENT);
				regret(move, getPlayer(CURRENT));
				if (!check)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Game::isCastlingAvaliable(const vector<Position>& path, CastlingType castlingType)
{
	for (Unit* unit : getPlayer(CURRENT).getSet())
	{
		if (!unit->isCastlingAvaliable(castlingType))
		{
			return false;
		}
	}
	return true;
}

void Game::commitCastling(CastlingType castlingType)
{

}

bool Game::isClear(vector<Position> path)
{
	// Path is clear of any unit, friendly or not
	return !getPlayer(CURRENT).hasUnitsIn(path) && !getPlayer(OPPONENT).hasUnitsIn(path);
}

void Game::regret(Move move, Player& opponent)
{
	// Reverses move's affection over game status
	move.moved->move(move.source);
	opponent.insertUnit(move.taken);
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
string Game::nextMove(string moveRepr, MoveDetails& moveReport)
{
	moveReport.promotionAvaliable = false;
	moveReport.needsReopen = false;
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
		Unit* unit = getPlayer(CURRENT).getUnit(src);
		// Check src and dst
		if (unit == nullptr) // Current player has no units in src
		{
			return SRC_NOT_OCUUPIED;
		}
		if (getPlayer(CURRENT).getUnit(dst) != nullptr) // Current player ha a unit in dst
		{
			return DST_OCCUPIED;
		}
		// Flags
		MovementFlags flags = { 0 };
		// Check if src can move to dst
		vector<Position> path = unit->pathToPosition(dst, flags, getPlayer(OPPONENT).getUnit(dst) != nullptr, getPlayer(CURRENT).getDirection());
		if (isClear(path))
		{
			// Save move for the opportunity to regret
			Move move = commitMove(unit, dst, getPlayer(OPPONENT));
			// If move causes check on current player its illegal
			if (!isCheckTo(CURRENT)) // Legal move!
			{
				// Check if move is a castling move and terminate move if such castling not avaliable
				if (flags.castling != None)
				{
					if (isCastlingAvaliable(path, flags.castling))
					{
						commitCastling(flags.castling);
					}
					else
					{
						return ILLEGAL_MOVEMENT;
					}
				}
				// Check if move caused checkmate
				if (isCheckmate())
				{
					return CHECKMATE;
				}
				// Delete taken unit (if any unit was taken)
				if (move.taken)
				{
					delete move.taken;
				}
				// Set the move report
				moveReport.moved = unit;
				moveReport.promotionAvaliable = flags.promotion;
				moveReport.needsReopen = flags.promotion || flags.castling != None || flags.enPassant;
				// Save status before changing current player
				string status = isCheckTo(OPPONENT) ? CHECK : OK;
				// Change player
				_currentPlayerIndicator = !_currentPlayerIndicator;
				// Return saved status
				return status;
			}
			else // Move caused check to current player
			{
				regret(move, getPlayer(OPPONENT));
				return MOVE_CAUSES_SELF_CHECK;
			}
		}
		else // Path is not clear
		{
			return ILLEGAL_MOVEMENT;
		}
	}
	catch (OutOfBoardException e) // Src or dst are not valid positions
	{
		return OUT_OF_BOARD;
	}
	catch (UnreachablePositionException e) // Dst unreachable by user
	{
		return ILLEGAL_MOVEMENT;
	}
}

string Game::getBoardRepr() const
{
	// Generate empty board
	string repr = "";
	repr.assign(64, '#');
	// Put both sets on the board
	_player1.affect(repr, true); // White
	_player2.affect(repr, false); // Black
	// Add player indicator
	repr += _currentPlayerIndicator ? '0' : '1';
	// Return full board representation
	return repr;
}

bool Game::promote(Unit* unit, char optionRepr)
{
	Player& currentPlayer = getPlayer(CURRENT);
	Unit* newUnit = nullptr;
	switch (optionRepr)
	{
	//case 'q':
	//	newUnit = new Queen(unit->getPos());
	//	break;
	case 'r':
		newUnit = new Rook(unit->getPos(), None);
		break;
	case 'b':
		newUnit = new Bishop(unit->getPos());
		break;
	case 'n':
		newUnit = new Knight(unit->getPos());
		break;
	default:
		return false;
	}
	currentPlayer.takeUnit(unit);
	currentPlayer.insertUnit(newUnit);
	return true;
}
