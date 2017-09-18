#include "../include/paddle.h"

//initialize a paddle, center in y direction
void Paddle::init (float x, float windowHeight, int w, int l, int side)
{
	this -> x = x;
	this -> y = windowHeight/2 - l/2;
	this -> windowHeight = windowHeight;
	this -> width = w;
	this -> length = l;
	this -> side = side;
}

//move paddle up one time
void Paddle::moveUp(int frameDelta)
{
	if (y > 0)
	{
		y -= frameDelta;
	}
}

//move paddle down one time
void Paddle::moveDown(int frameDelta)
{
	if ( y + length < windowHeight)
	{
		y += frameDelta;
	}
}

//set x when window is resized
void Paddle::setX(float newX)
{
	x = newX;
}

//update window height
void Paddle::setWindowHeight(float newHeight)
{
	windowHeight = newHeight;
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
