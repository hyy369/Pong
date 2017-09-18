#include "../include/ball.h"
#include "../include/paddle.h"
#include "../include/pong.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>

// center the ball and randomly generate a starting movement heading the positive
// direction on x, and between -1 and 1 on y direction.
void Ball::init (float windowWidth, float windowHeight, int r)
{
  this -> centerX = windowWidth/2;
  this -> centerY = windowHeight/2;
  this -> windowWidth = windowWidth;
  this -> windowHeight = windowHeight;
  this -> radius = r;
  this -> speedX = 1;
  this -> speedY = float(rand()) / float(RAND_MAX) * 2 - 1;
  normalizeSpeed();
}

//move the ball one time, return if the ball has collided a wall
bool Ball::move(int frameDelta)
{
  if ( (getUpperY() <= 0.0 && speedY < 0.0) || (getLowerY() >= windowHeight && speedY > 0.0))
  {
    collideWall();
    return true;
  }
  if (getLeftX() >= 0.0 && getRightX() <= windowWidth)
  {
    centerX += speedX * frameDelta;
    centerY += speedY * frameDelta;
  }
  return false;
}

//normalize speed vector
void Ball::normalizeSpeed()
{
  speedX = speedX / sqrt(speedX * speedX + speedY * speedY);
  speedY = speedY / sqrt(speedX * speedX + speedY * speedY);
}

//reflect speed vector if collides a wall, multiply by random number in [0.9, 1.1]
void Ball::collideWall()
{
  speedY = -speedY * (float(rand()) / float(RAND_MAX) * 0.2 + 1);
  normalizeSpeed();
}

//update window size
void Ball::setWindowSize(float w, float h)
{
  windowWidth = w;
  windowHeight = h;
}

//reflect speed vector if collides a paddle, multiply by random number in [0.9, 1.1]
//returns if ball did collede a paddle
bool Ball::didCollidePaddle(Paddle paddle)
{
  if ( (paddle.getSide() == 0) &&
       (getLeftX() <= paddle.getRightX()) &&
       (getLeftX() <= paddle.getLeftX()) &&
       (centerY >= paddle.getUpperY()) &&
       (centerY <= paddle.getLowerY()) &&
       speedX < 0) {
    // playPaddleSound();
    speedX = -speedX * (float(rand()) / float(RAND_MAX) * 0.2 + 1);
    normalizeSpeed();
    return true;
  } else if ( (paddle.getSide() == 1) &&
       (getRightX() >= paddle.getLeftX()) &&
       (getRightX() <= paddle.getRightX()) &&
       (centerY >= paddle.getUpperY()) &&
       (centerY <= paddle.getLowerY()) &&
      speedX > 0) {
    // playPaddleSound();
    speedX = -speedX * (float(rand()) / float(RAND_MAX) * 0.2 + 1);
    normalizeSpeed();
    return true;
  }
  return false;
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

float Ball::getCenterX()
{
  return centerX;
}

float Ball::getCenterY()
{
  return centerY;
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
