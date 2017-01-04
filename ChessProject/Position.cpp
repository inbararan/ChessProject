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

bool Position::sameFile(Position pos) const
{
	return _file == pos._file;
}

bool Position::sameRank(Position pos) const
{
	return _rank == pos._rank;
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

vector<Position> Position::positionsRangeOnFile(char file, int rankLimit1, int rankLimit2)
{
	vector<Position> positions = vector<Position>();
	for (int r = MIN(rankLimit1, rankLimit2) + 1; r < MAX(rankLimit1, rankLimit2); r++)
	{
		positions.push_back(Position(file, r));
	}
	return positions;
}

vector<Position> Position::positionsRangeOnRank(int rank, char fileLimit1, char fileLimit2)
{
	vector<Position> positions = vector<Position>();
	for (int f = MIN(fileLimit1, fileLimit2) + 1; f < MAX(fileLimit1, fileLimit2); f++)
	{
		positions.push_back(Position(f, rank));
	}
	return positions;
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
