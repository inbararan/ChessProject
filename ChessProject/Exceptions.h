#pragma once

#include <exception>

using namespace std;

// Position::Position throws if row or col out of borders
class OutOfBoardException : exception
{
};

// Unit::pathToPosition throws if dest unrachable
class UnreachablePositionException : exception
{
};

// Unit::pathToPosition throws if dest equals to current position of unit
class DestinationIsPositionException : exception
{
};
