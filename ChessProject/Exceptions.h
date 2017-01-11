#pragma once

#include <exception>

using namespace std;

class OutOfBoardException : exception
{
};

class UnknownDirectionException : exception
{
};

class UnreachablePositionException : exception
{
};

class IllegalMovement : exception
{
};

class SteppingIntoFire : exception
{
};