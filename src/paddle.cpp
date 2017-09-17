#include "../include/paddle.h"
#include <stdlib.h>


Paddle::Paddle (int x, int y, int l)
{
	this -> x = x;
	this -> y = y;
	this -> length = l;
}

void Paddle::moveUp(void)
{
	y--;
}

void Paddle::moveDown(void)
{
	y++;
}

int Paddle::getX(void)
{
	return this -> x;
}

int Paddle::getY(void)
{
	return this -> y;
}

int Paddle::getLength(void)
{
	return length;
}
