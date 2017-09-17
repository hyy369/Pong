#include "../include/ball.h"
#include "../include/paddle.h"

void Ball::init (float x, float y, int r)
{
  this -> centerX = x;
  this -> centerY = y;
  this -> radius = r;
  this -> speedX = 0.2;
  this -> speedY = 0.2;
}

void Ball::move()
{
  if ( (getUpperY() <= 0.0 && speedY < 0.0) || (getLowerY() >= 600.0 && speedY > 0.0))
  {
    collideWall();
  }

  if (getLeftX() >= 0.0 && getRightX() <= 800.0)
  {
    centerX += speedX;
    centerY += speedY;
  }
}

void Ball::collideWall()
{
  speedY = -speedY;
}

void Ball::checkCollidePaddle(Paddle paddle)
{
  if ( (paddle.getSide() == 0) &&
       (getLeftX() <= paddle.getRightX()) &&
       (getLowerY() >= paddle.getUpperY()) &&
       (getUpperY() <= paddle.getLowerY())) {
    speedX = -speedX;
  } else if ( (paddle.getSide() == 1) &&
       (getRightX() >= paddle.getLeftX()) &&
       (getLowerY() >= paddle.getUpperY()) &&
       (getUpperY() <= paddle.getLowerY())) {
    speedX = -speedX;
  }
}

float Ball::getLeftX()
{
  return centerX - radius;
}

float Ball::getRightX()
{
  return centerX + radius;
}

float Ball::getUpperY()
{
  return centerY - radius;
}

float Ball::getLowerY()
{
  return centerY + radius;
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
