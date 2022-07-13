#include "coordinate.h"
#include <math.h>

Coordinate::Coordinate(const Coordinate &other)
{
    row = other.row;
    col = other.col;
}

int Coordinate::distance(Coordinate other)
{
    return abs(other.col - col) + abs(other.row - row);
}
