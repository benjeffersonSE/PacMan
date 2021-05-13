#include "Ghost.h"

Ghost::Ghost() : symbol(GHOST), x(0), y(0), dx(0), dy(0)
{
}

Ghost::Ghost(int x, int y)
{
    symbol = GHOST;
    this->x = x;
    this->y = y;
}


const void Ghost::Move(int direction)
{
	switch (direction)
	{
	case KEY_LEFT:
		dx = -1;
		dy = 0;
		break;
	case KEY_RIGHT:
		dx = +1;
		dy = 0;
		break;
	case KEY_UP:
		dx = 0;
		dy = -1;
		break;
	case KEY_DOWN:
		dx = 0;
		dy = +1;
		break;
	default:
		// not a key we care about, so do nothing
		break;
	}

	// update mouse coordinates if move is possible
	if (((x + dx) >= 1) && ((x + dx) <= SIZE) && ((y + dy) >= 1) && ((y + dy) <= SIZE))
	{
		UpdatePosition(dx, dy);
	}
}

const void Ghost::UpdatePosition(int dx, int dy)
{
	x += dx;
	y += dy;
}

const int Ghost::GetX() const
{
	return x;
}

const int Ghost::GetY() const
{
	return y;
}

const bool Ghost::IsAtPosition(int x, int y) const
{
	return this->x == x && this->y == y;
}

const int Ghost::getDirection() const
{
	return direction;
}

const void Ghost::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}