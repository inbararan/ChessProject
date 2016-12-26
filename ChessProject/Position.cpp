#include "Position.h"

Position::Position(string repr)
{
	if (repr[0] > MAX_FILE || repr[0] < MIN_FILE || repr[1] > MAX_RANK || repr[1] < MIN_RANK)
	{
		throw OutOfBoardException();
	}
	_file = repr[0];
	_rank = repr[1] - '0';
}

Position::Position(char file, int rank)
{
	if (file > MAX_FILE || file < MIN_FILE || rank > MAX_RANK || rank < MIN_RANK)
	{
		throw OutOfBoardException();
	}
	_file = file;
	_rank = rank;
}

int Position::index() const
{
	return (_file - MIN_FILE) * BOARD_SIZE + (_rank - MIN_RANK);
}

bool Position::operator==(const Position& other) const
{
	return _file == other._file && _rank == other._rank;
}
