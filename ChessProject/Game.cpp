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

bool Game::isClear(vector<Position> path)
{
	// Path is clear of any unit, friendly or not
	return !getPlayer(CURRENT).hasUnitsIn(path) && !getPlayer(OPPONENT).hasUnitsIn(path);
}

bool Game::isReachable(Unit* unit, Position dst)
{
	vector<Position> path = vector<Position>();
	try
	{
		// All positions unit should pass in order to get to dst
		path = unit->pathToPosition(dst, getPlayer(OPPONENT).getUnit(dst) != nullptr, getPlayer(CURRENT).getDirection());
	}
	catch (UnreachablePositionException) // Position is unreachable by dst
	{
		return false;
	}
	// The path should be clear
	return isClear(path);
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
	Player& current = getPlayer(CURRENT);
	Player& opponent = getPlayer(OPPONENT);
	for (Unit* optionalSaver : opponent.getSet())
	{
		cout << "Unit in " << optionalSaver->getPos().get_repr() << endl;
		for (Position pos : Position::allPossiblePositions())
		{
			if (isReachable(optionalSaver, pos))
			{
				cout << "Considerable move: " << optionalSaver->getPos().get_repr() << pos.get_repr() << endl;
				Move move = commitMove(optionalSaver, pos, current);
				bool check = isCheckTo(OPPONENT);
				regret(move, current);
				if (!check)
				{
					cout << "Move : " << move.source.get_repr() << pos.get_repr() << " saves the day!" << endl;
					return false;
				}
			}
		}
	}
	return true;
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
		// Check if src can move to dst
		if (isReachable(unit, dst))
		{
			// Save move for the opportunity to regret
			Move move = commitMove(unit, dst, getPlayer(OPPONENT));
			// If move causes check on current player its illegal
			if (!isCheckTo(CURRENT)) // Legal move!
			{
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
