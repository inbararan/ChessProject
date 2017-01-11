#include "Game.h"

Player& Game::getPlayer(bool playerIndicator)
{
	return playerIndicator ? _player1 : _player2;
}

FullMove Game::commitMove(Unit* toMove, Position dest, Player& opponent)
{
	FullMove move = { toMove, toMove->getPos(), opponent.getUnit(dest) };
	toMove->move(dest);
	opponent.takeUnit(move.taken);
	return move;
}

bool Game::isDangeredBy(const Position& pos, bool opponentPlayerIndicator)
{
	for (Unit* opponentUnit : getPlayer(opponentPlayerIndicator).getSet())
	{
		//cout << opponentUnit->getPos().get_repr() << " might danger " << pos.get_repr() << endl;
		try
		{
			if (isClear(getPath(opponentUnit, pos, !opponentPlayerIndicator)))
			{
				cout << opponentUnit->getPos().get_repr() << " dangers " << pos.get_repr() << endl;
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

bool Game::isDangeredBy(vector<Position> positions, bool opponentPlayerIndicator)
{
	for (Position pos : positions)
	{
		if (isDangeredBy(pos, opponentPlayerIndicator))
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
		if (isDangeredBy(vital->getPos(), !playerIndicator))
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
					path = getPath(optionalSaver, pos, CURRENT);
				}
				catch (UnreachablePositionException e)
				{
					// pos unreachable by optionalSaver
					continue;
				}
				if (isClear(path)) // Path must be clear
				{
					FullMove move = commitMove(optionalSaver, pos, getPlayer(CURRENT));
					bool check = isCheckTo(OPPONENT);
					regret(move, getPlayer(CURRENT));
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
			vector<Position> path = getPath(unit, move.dest, OPPONENT);
			if (isClear(path) && !(unit->vital() && (isDangeredBy(move.dest, OPPONENT) || isDangeredBy(path, OPPONENT))))
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
		return true;
	}
	else // Only one (or none) of the units can castle this castling type
	{
		return false;
	}
}

vector<Position> Game::getPath(Unit* unit, const Position& dest, bool opponentIndicator)
{
	MovementFlags flags = DEFAULT_FLAGS;
	return getPath(unit, flags, dest, getPlayer(opponentIndicator).getUnit(dest) != nullptr);
}

vector<Position> Game::getPath(Unit* unit, bool enemyThereToPush, const Position& dest)
{
	MovementFlags flags = DEFAULT_FLAGS;
	return getPath(unit, flags, dest, enemyThereToPush);
}

vector<Position> Game::getPath(Unit* unit, MovementFlags& flags, bool enemyThere, const Position& dest)
{
	vector<Position> path = unit->pathToPosition(dest, flags);
	if (flags.avaliability == Unreachable ||
		(flags.avaliability == Regular && enemyThere) ||
		(flags.avaliability == Capture && !enemyThere))
	{
		throw UnreachablePositionException();
	}
	return path;
}

vector<Position> Game::getPath(Unit* unit, MovementFlags& flags, const Position& dest, bool opponentIndicator)
{
	vector<Position> path = unit->pathToPosition(dest, flags);
	if ((flags.avaliability == Unreachable) ||
		((flags.avaliability == Regular) && (getPlayer(opponentIndicator).getUnit(dest) != nullptr)) ||
		((flags.avaliability == Capture) && (getPlayer(opponentIndicator).getUnit(dest) == nullptr)) ||
		(flags.moveDirection & getPlayer(opponentIndicator).getDirection() == 0)) // Direction flag doesn't player direction
	{
		throw UnreachablePositionException();
	}
	return path;
}

bool Game::isClear(vector<Position> path)
{
	// Path is clear of any unit, friendly or not
	return !getPlayer(CURRENT).hasUnitsIn(path) && !getPlayer(OPPONENT).hasUnitsIn(path);
}

void Game::regret(FullMove move, Player& opponent)
{
	// Reverses move's affection over game status
	move.moved->regretMove(move.source);
	opponent.insertUnit(move.taken);
}

void Game::validateMoveLegality(Unit* unit, const Position& dest, MoveReport& report) // For current player
{
	MovementFlags flags = DEFAULT_FLAGS;
	// Check if src can move to dst
	vector<Position> path = vector<Position>();
	try
	{
		path = getPath(unit, flags, dest, OPPONENT);
	}
	catch (UnreachablePositionException e)
	{
		throw IllegalMovement();
	}
	if (flags.castling) // Move is castling
	{
		if (!isCheckTo(CURRENT) && castleIfAvaliable(flags.castling))
		{
			report.needsReopen = true;
		}
		else
		{
			throw IllegalMovement();
		}
	}
	else if (isClear(path)) // Regular move
	{
		// Save move for the opportunity to regret
		FullMove move = commitMove(unit, dest, getPlayer(OPPONENT));
		// If move causes check on current player its illegal
		if (!isCheckTo(CURRENT)) // Legal move!
		{
			// Remove taken unit to avoid memory leaks
			if (move.taken)
			{
				delete move.taken;
			}
			// Main program should be informed about promotion & reopen to handle such events
			report.moved = unit;
			report.promotionAvaliable = unit->canPromote() && dest.inPromotionRank(getPlayer(CURRENT).getDirection());
			report.needsReopen = report.promotionAvaliable; // Add enPassant
		}
		else // Move caused check to current player
		{
			regret(move, getPlayer(OPPONENT));
			throw SteppingIntoFire();
		}
	}
	else // Path is not clear
	{
		throw IllegalMovement();
	}
}

Game::Game() : _player1(Player(Up)), _player2(Player(Down))
{
	_currentPlayerIndicator = WHITE;
}
string Game::nextMove(string moveRepr, MoveReport& report)
{
	// Init report to default value so the former report won't get into it
	report = { nullptr, false, false };
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
		validateMoveLegality(unit, dst, report);
	}
	catch (OutOfBoardException e) // Src or dst are not valid positions
	{
		return OUT_OF_BOARD;
	}
	catch (IllegalMovement e) // Dst unreachable by user
	{
		return ILLEGAL_MOVEMENT;
	}
	catch (SteppingIntoFire e)
	{
		return MOVE_CAUSES_SELF_CHECK;
	}
	// No exception was thrown!
	// End turn:
	// Save status befor current player changes
	string status = OK;
	if (isCheckTo(OPPONENT))
	{
		status = CHECK;
		if (isCheckmate())
		{
			status = CHECKMATE;
		}
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
	Player& currentPlayer = getPlayer(!CURRENT); // Player indicator already changed:/
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
		return true;
	}
	currentPlayer.takeUnit(unit);
	currentPlayer.insertUnit(newUnit);
	return false;
}
