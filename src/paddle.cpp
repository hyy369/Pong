#include "../include/paddle.h"
#include <stdlib.h>

void Paddle::init (int x, int y, int l)
{
	this -> x = x;
	this -> y = y;
	this -> length = l;
}

void Paddle::moveUp(void)
{
	if (y > 0) {y--;}
}

void Paddle::moveDown(void)
{
	if ( y + length < 600) {y++;}
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
