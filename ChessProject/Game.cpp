#include "Game.h"

Player& Game::getPlayer(bool playerIndicator)
{
	return playerIndicator ? _player1 : _player2;
}

Move Game::commitMove(Unit* toMove, Position dest, Player& opponent)
{
	Move move = { toMove, toMove->getPos(), opponent.getUnit(dest) };
	if (dest == Position('c', 7))
		cout << endl;
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
			if (isClear(opponentUnit->pathToPosition(pos, true)))
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
					path = getPath(optionalSaver, pos, OPPONENT);
				}
				catch (UnreachablePositionException e)
				{
					// pos unreachable by optionalSaver
					continue;
				}
				if (isClear(path)) // Path must be clear
				{
					if (pos == Position('c', 7))
						cout << endl;
					Move move = commitMove(optionalSaver, pos, getPlayer(CURRENT));
					bool check = isCheckTo(OPPONENT);
					regret(move, getPlayer(CURRENT));
					cout << move.source.get_repr() << pos.get_repr() << " might save the day..." << endl;
					if (!check) // That move removes the check!
					{
						cout << move.source.get_repr() << pos.get_repr() << " saves the day!" << endl;
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
	cout << "CASTLING" << endl;
	vector<SimpleMove> relevantMoves = vector<SimpleMove>();
	char destFile = ' ';
	// Collect units that will be involved
	for (Unit* unit : getPlayer(CURRENT).getSet())
	{
		if (unit->castlingRelevant(castlingType, destFile))
		{
			cout << "Castling relevant to " << unit->getPos().get_repr() << endl;
			SimpleMove move = { unit, Position(destFile, unit->getPos().getRank()) };
			vector<Position> path = getPath(unit, move.dest, CURRENT);
			cout << isClear(path) << unit->vital() << isDangeredBy(move.dest, OPPONENT) << isDangeredBy(path, OPPONENT) << endl;
			if (isClear(path) && !(unit->vital() && (isDangeredBy(move.dest, OPPONENT) || isDangeredBy(path, OPPONENT))))
			{
				cout << "Castling fine with " << unit->getPos().get_repr() << endl;
				relevantMoves.push_back(move);
			}
		}
	}
	if (relevantMoves.size() > 1) // Cannot castle with only one unit, it takes two to tango
	{
		for (SimpleMove move : relevantMoves)
		{
			cout << "Finally moving (castling) " << move.toBeMoved->getPos().get_repr() << " to " << move.dest.get_repr() << endl;
			move.toBeMoved->move(move.dest);
		}
		return true;
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
	move.moved->regretMove(move.source);
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
	cout << "MOVING" << endl;
	for (Unit* u : getPlayer(CURRENT).getSet())
		cout << "C : " << u->repr(false) << " : " << u->getPos().get_repr() << endl;
	for (Unit* u : getPlayer(OPPONENT).getSet())
		cout << "O : " << u->repr(false) << " : " << u->getPos().get_repr() << endl;
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
			if (!isCheckTo(CURRENT) && castleIfAvaliable(flags.castling))
			{
				moveReport.needsReopen = true;
			}
			else
			{
				return ILLEGAL_MOVEMENT;
			}
		}
		else if (isClear(path)) // Regular move
		{
			// Save move for the opportunity to regret
			Move move = commitMove(unit, dst, getPlayer(OPPONENT));
			// If move causes check on current player its illegal
			if (moveRepr == "a7a8")
				cout << endl;
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
				moveReport.needsReopen = flags.enPassant || moveReport.promotionAvaliable;
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
		if (isCheckmate())
		{
			status = CHECKMATE;
			moveReport.needsReopen = true;
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
