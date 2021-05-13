#include "Clyde.h"

Clyde::Clyde() : symbol(CLYDE), x(0), y(0), dx(0), dy(0)
{

}

const int Clyde::getDirection()
{
	return direction = rand() % 4 + 262;
}