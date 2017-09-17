#include "../include/ball.h"
#include "../include/paddle.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>

void Ball::init (float x, float y, int r)
{
  this -> centerX = x;
  this -> centerY = y;
  this -> radius = r;
  this -> speedX = 1;
  this -> speedY = float(rand()) / float(RAND_MAX) * 2 - 1;
  normalizeSpeed();
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

void Ball::normalizeSpeed()
{
  speedX = speedX / sqrt(speedX * speedX + speedY * speedY);
  speedY = speedY / sqrt(speedX * speedX + speedY * speedY);
}

void Ball::collideWall()
{
  speedY = -speedY * (float(rand()) / float(RAND_MAX) * 0.2 + 1);
  normalizeSpeed();
}

void Ball::checkCollidePaddle(Paddle paddle)
{
  if ( (paddle.getSide() == 0) &&
       (getLeftX() <= paddle.getRightX()) &&
       (getLeftX() <= paddle.getLeftX()) &&
       (centerY >= paddle.getUpperY()) &&
       (centerY <= paddle.getLowerY())) {
    speedX = -speedX;
  } else if ( (paddle.getSide() == 1) &&
       (getRightX() >= paddle.getLeftX()) &&
       (getRightX() <= paddle.getRightX()) &&
       (centerY >= paddle.getUpperY()) &&
       (centerY <= paddle.getLowerY())) {
    speedX = -speedX * (float(rand()) / float(RAND_MAX) * 0.2 + 1);
    normalizeSpeed();
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
