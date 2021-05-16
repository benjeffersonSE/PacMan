#include "Clyde.h"

Clyde::Clyde() : symbol(CLYDE), x(0), y(0), dx(0), dy(0)
{

}

Clyde::Clyde(int x, int y) : symbol(CLYDE), x(x), y(y), dx(0), dy(0)
{
	this->setPosition(x, y);
}

string Clyde::getGhostName() const
{
	return "Clyde";
}