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

bool Game::isDangeredBy(const Position& pos, bool playerIndicator)
{
	for (Unit* opponentUnit : getPlayer(!playerIndicator).getSet())
	{
		try
		{
			if (isClear(opponentUnit->pathToPosition(pos, true)))
			{
				return true;
			}
		}
		catch (UnreachablePositionException e)
		{
			// vital unrachable by opponentUnit, thats all
		}
	}
	return false;
}

bool Game::isDangeredBy(vector<Position> positions, bool playerIndicator)
{
	for (Position pos : positions)
	{
		if (isDangeredBy(pos, playerIndicator))
		{
			return true;
		}
	}
	return false;
}

bool Game::isCheckTo(bool playerIndicator)
{
	vector<Unit*> vitals = getPlayer(playerIndicator).vitalUnits();
	for (Unit* vital : vitals)
	{
		if (isDangeredBy(vital->getPos(), playerIndicator))
		{
			return true;
		}
	}
	return false;
}

bool Game::isCheckmate() // To opponent
{
	/*
	If no opponent unit can do anything that removes the check, it's a checkmate
	*/
	for (Unit* optionalSaver : getPlayer(OPPONENT).getSet())
	{
		/*
		Check every possibe move (whole board)
		*/
		for (Position pos : Position::allPossiblePositions())
		{
			// optionalSaver cannot move to a position taken by his own color
			if (getPlayer(OPPONENT).getUnit(pos) == nullptr)
			{
				vector<Position> path = vector<Position>();
				try
				{
					path = optionalSaver->pathToPosition(pos, getPlayer(CURRENT).getUnit(pos) != nullptr);
				}
				catch (UnreachablePositionException e)
				{
					// pos unreachable by optionalSaver
					continue;
				}
				if (isClear(path)) // Path must be clear
				{
					Move move = commitMove(optionalSaver, pos, getPlayer(OPPONENT));
					bool check = isCheckTo(OPPONENT);
					regret(move, getPlayer(OPPONENT));
					if (!check) // That move removes the check!
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool Game::castleIfAvaliable(CastlingType castlingType)
{
	vector<SimpleMove> relevantMoves = vector<SimpleMove>();
	char destFile = ' ';
	// Collect units that will be involved
	for (Unit* unit : getPlayer(CURRENT).getSet())
	{
		if (unit->castlingRelevant(castlingType, destFile))
		{
			SimpleMove move = { unit, Position(destFile, unit->getPos().getRank()) };
			vector<Position> path = getPath(unit, move.dest, CURRENT);
			if (isClear(path) && !(unit->vital() && isDangeredBy(path, OPPONENT)))
			{
				relevantMoves.push_back(move);
			}
		}
	}
	if (relevantMoves.size() > 1) // Cannot castle with only one unit, it takes two to tango
	{
		for (SimpleMove move : relevantMoves)
		{
			move.toBeMoved->move(move.dest);
		}
	}
	else // Only one (or none) of the units can castle this castling type
	{
		return false;
	}

}

vector<Position> Game::getPath(Unit* unit, const Position& dest, bool playerIndicator)
{
	return unit->pathToPosition(dest, getPlayer(!playerIndicator).hasUnitIn(dest));
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
string Game::nextMove(string moveRepr, MoveReport& moveReport)
{
	// Init report to default value so the former report won't get into it
	moveReport = { nullptr, false, false };
	try
	{
		Position src = Position(moveRepr.substr(0, 2));
		Position dst = Position(moveRepr.substr(2, 2));
		if (src == dst) // There must be a movement
		{
			return DST_EQL_SRC;
		}
		Unit* unit = getPlayer(CURRENT).getUnit(src);
		if (unit == nullptr) // Current player has no units in src
		{
			return SRC_NOT_OCUUPIED;
		}
		if (getPlayer(CURRENT).getUnit(dst) != nullptr) // Current player has a unit in dst
		{
			return DST_OCCUPIED;
		}
		MovementFlags flags = { None, false };
		// Check if src can move to dst
		vector<Position> path = unit->pathToPosition(dst, flags, getPlayer(OPPONENT).getUnit(dst) != nullptr);
		if (flags.castling) // Move is castling
		{
			if (castleIfAvaliable(flags.castling))
			{
				moveReport.needsReopen = true;
			}
		}
		else if (isClear(path)) // Regular move
		{
			// Save move for the opportunity to regret
			Move move = commitMove(unit, dst, getPlayer(OPPONENT));
			// If move causes check on current player its illegal
			if (!isCheckTo(CURRENT)) // Legal move!
			{
				// Remove taken unit to avoid memory leaks
				if (move.taken)
				{
					delete move.taken;
				}
				// Main program should be informed about promotion & reopen to handle such events
				moveReport.moved = unit;
				moveReport.promotionAvaliable = unit->canPromote() && dst.inPromotionRank(getPlayer(CURRENT).getDirection());
				moveReport.needsReopen = flags.enPassant;
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
	// End turn:
	// Save status befor current player changes
	string status = OK;
	if (isCheckTo(OPPONENT))
	{
		status = CHECK;
	}
	else if (isCheckmate())
	{
		status = CHECKMATE;
	}
	_currentPlayerIndicator = !_currentPlayerIndicator;
	return status;
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
	case 'q':
		newUnit = new Queen(unit->getPos());
		break;
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
