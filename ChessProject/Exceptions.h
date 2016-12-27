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

// Position::Position (one overload) throws if playerDirection is not Up nor Down
class UnknownDirectionException : exception
{
};
