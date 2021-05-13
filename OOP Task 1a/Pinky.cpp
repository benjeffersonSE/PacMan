#include "Pinky.h"

Pinky::Pinky() : symbol(PINKY), x(0), y(0), dx(0), dy(0)
{

}

string Pinky::getGhostName() const
{
	return "Pinky";
}