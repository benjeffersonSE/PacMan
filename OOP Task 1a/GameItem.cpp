#include "GameItem.h"

GameItem::GameItem() : symbol(GAMEITEM), x(0), y(0)
{
}

GameItem::GameItem(int x, int y)
{
	symbol = GAMEITEM;
	this->x = x;
	this->y = y;
}

const int GameItem::GetX() const
{
	return x;
}

const int GameItem::GetY() const
{
	return y;
}

const bool GameItem::IsAtPosition(int x, int y) const
{
	return this->x == x && this->y == y;

}

const void GameItem::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}