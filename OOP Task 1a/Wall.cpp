#include "Wall.h"

Wall::Wall()
{
}

Wall::Wall(int x, int y)
{
    symbol = WALL;
    this->x = x;
    this->y = y;
}

const int Wall::GetX() const
{
    return x;
}

const int Wall::GetY() const
{
    return y;
}

const bool Wall::IsAtPosition(int x, int y) const
{
    return this->x == x && this->y == y;
}