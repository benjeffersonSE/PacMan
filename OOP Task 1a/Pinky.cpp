#include "Pinky.h"

Pinky::Pinky() : symbol(PINKY), x(0), y(0), dx(0), dy(0)
{

}

const int Pinky::getDirection()
{
	return direction = rand() % 4 + 262;
}