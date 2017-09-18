#include "../include/paddle.h"

void Paddle::init (float x, float y, int w, int l, int side)
{
	this -> x = x;
	this -> y = y;
	this -> width = w;
	this -> length = l;
	this -> side = side;
}

void Paddle::moveUp()
{
	if (y > 0) {y--;}
}

void Paddle::moveDown()
{
	if ( y + length < 600) {y++;}
}

float Paddle::getLeftX()
{
	return x;
}

float Paddle::getRightX()
{
	return x + width;
}

float Paddle::getUpperY()
{
	return y;
}

float Paddle::getCenterY()
{
	return y + (float) length / 2;
}

float Paddle::getLowerY()
{
	return y + length;
}

int Paddle::getWidth ()
{
	return width;
}

int Paddle::getLength()
{
	return length;
}

int Paddle::getSide()
{
	return side;
}
