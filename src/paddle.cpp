#include "../include/paddle.h"

void Paddle::init (float x, float y, int l)
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

float Paddle::getX(void)
{
	return x;
}

float Paddle::getY(void)
{
	return y;
}

int Paddle::getLength(void)
{
	return length;
}
