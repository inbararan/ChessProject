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
	return (_file - MIN_FILE) * BOARD_SIZE + (_rank - MIN_RANK);
}

bool Position::operator==(const Position& other) const
{
	return _file == other._file && _rank == other._rank;
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
