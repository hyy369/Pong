#ifndef BALL_H
#define BALL_H

#include "../include/paddle.h"

class Ball
{
private:
  float centerX;
  float centerY;
  int radius;
  float speedX;
  float speedY;

public:
  Ball (){}
  void init (float, float, int);
  void move();
  void collideWall();
  void checkCollidePaddle(Paddle paddle);
  float getLeftX();
  float getRightX();
  float getUpperY();
  float getLowerY();
  float getSpeedX();
  float getSpeedY();
  int getRadius();
};

#endif
