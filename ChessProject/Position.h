#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Exceptions.h"

using namespace std;

#define MAX(x, y) ((x > y) ? (x) : (y))
#define MIN(x, y) ((x < y) ? (x) : (y))

#define MIN_FILE 'a'
#define MAX_FILE 'h'
#define MIN_RANK 1
#define MAX_RANK 8

#define BOARD_SIZE 8

enum Direction{Up = 1, Down = -1};

class Position
{
private:
	char _file; // col
	int _rank; //row
public:
	Position(string repr); // Throws exception if out of board borders
	Position(char file, int rank); // Throws exception if out of board borders
	
	char getFile() const;
	int getRank() const;

	bool sameFile(Position pos) const;
	bool sameRank(Position pos) const;

	int index() const; // Index in board repr
	bool operator==(const Position& other) const;

	static vector<Position> positionsRangeOnFile(char file, int minRank, int maxRank);
	static vector<Position> positionsRangeOnRank(int rank, char minFile, char maxFile);
};
