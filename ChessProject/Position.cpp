#include "Position.h"

Position::Position(char file, int rank)
{
	if (file > MAX_FILE || file < MIN_FILE || rank > MAX_RANK || rank < MIN_RANK)
	{
		throw OutOfBoardException();
	}
	_file = file;
	_rank = rank;
}

Position::Position(string repr) : Position(repr[0], repr[1] - '0')
{
}

Position::Position(char file, int relativeRank, Direction playerDirection) : Position(file, 1)
{
	// Getting relaive rank (first rank, second rank, etc.) and setting the absolute rank (Black's first rank is actually the 8'th)
	switch (playerDirection)
	{
	case Up:
		_rank = relativeRank;
		break;
	case Down:
		_rank = MAX_RANK + MIN_RANK - relativeRank;
		break;
	default:
		throw UnknownDirectionException();
	}
}

char Position::getFile() const
{
	return _file;
}

int Position::getRank() const
{
	return _rank;
}

bool Position::sameFile(const Position& other) const
{
	return _file == other._file;
}

bool Position::sameRank(const Position& other) const
{
	return _rank == other._rank;
}

int Position::index() const
{
	// Rank is row and file is column
	return (MAX_RANK - _rank) * BOARD_SIZE + (_file - MIN_FILE);
}

bool Position::operator==(const Position& other) const
{
	return _file == other._file && _rank == other._rank;
}

bool Position::operator!=(const Position& other) const
{
	return !(operator==(other));
}

bool Position::inPromotionRank(Direction playerDirection) const
{
	switch (playerDirection)
	{
	case Up:
		return _rank == MAX_RANK;
	case Down:
		return _rank == MIN_RANK;
	default:
		throw UnknownDirectionException();
	}
}

vector<Position> Position::allPossiblePositions()
{
	vector<Position> positions = vector<Position>();
	for (char f = MIN_FILE; f <= MAX_FILE; f++)
	{
		for (int r = MIN_RANK; r <= MAX_RANK; r++)
		{
			positions.push_back(Position(f, r));
		}
	}
	return positions;
}
