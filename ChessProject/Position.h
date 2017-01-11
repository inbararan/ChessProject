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

enum Direction{Up = 0x2, Down = 0x1};

typedef char direction_t;

class Position
{
private:
	char _file; // col
	int _rank; //row
public:
	Position(char file, int rank); // Throws exception if out of board borders
	Position(string repr); // Throws exception if out of board borders
	Position(char file, int relativeRank, Direction direction); // Throws exception if out of board borders
	
	char getFile() const;
	int getRank() const;
	string get_repr () const { string repr = ""; repr += _file; repr += _rank + '0'; return repr; };

	bool sameFile(Position pos) const;
	bool sameRank(Position pos) const;

	int index() const; // Index in board repr
	bool operator==(const Position& other) const;
	bool operator!=(const Position& other) const;
	bool inPromotionRank(Direction playerDirection) const;

	static vector<Position> allPossiblePositions(); // All possible positions on board
};
