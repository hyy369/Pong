#include "../include/ball.h"

void Ball::init (float x, float y, int r)
{
  this -> centerX = x;
  this -> centerY = y;
  this -> radius = r;
  this -> leftX = x - r;
  this -> rightX = x + r;
  this -> upperY = y - r;
  this -> lowerY = y + r;
  this -> speedX = 0.2;
  this -> speedY = 0.2;
}

void Ball::move()
{
  if ( (upperY < 0.0) || (lowerY > 600.0))
  {
    reflect();
  }
  centerX += speedX;
  centerY += speedY;
  updateEdges();
  // x += speedX;
  // y += speedY;
}

void Ball::reflect()
{
  speedY = -speedY;
}

void Ball::updateEdges()
{
  leftX = centerX - radius;
  rightX = centerX + radius;
  upperY = centerY - radius;
  lowerY = centerY + radius;
}

float Ball::getLeftX()
{
  return leftX;
}

float Ball::getUpperY()
{
  return upperY;
}

float Ball::getSpeedX()
{
  return speedX;
}

float Ball::getSpeedY()
{
  return speedY;
}

int Ball::getRadius()
{
  return radius;
}
