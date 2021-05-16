#include "Pinky.h"

Pinky::Pinky() : symbol(PINKY), x(0), y(0), dx(0), dy(0)
{

}

Pinky::Pinky(int x, int y) : symbol(PINKY), x(x), y(y), dx(0), dy(0)
{
	this->setPosition(x, y);
}

string Pinky::getGhostName() const
{
	return "Pinky";
}