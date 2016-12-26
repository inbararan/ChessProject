#include "Queen.h"

Queen::Queen(Position pos) : Unit(pos)
{

}

char Queen::repr() const
{
	return 'q';
}
