#include "Blinky.h"

Blinky::Blinky() : symbol(BLINKY), x(0), y(0), dx(0), dy(0)
{

}

Blinky::Blinky(int x, int y) : symbol(BLINKY), x(x), y(y), dx(0), dy(0)
{
	this->setPosition(x, y);
}

string Blinky::getGhostName() const
{
	return "Blinky";
}