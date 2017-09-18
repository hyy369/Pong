#ifndef BALL_H
#define BALL_H

#include "../include/paddle.h"

class Ball
{
private:
  float centerX;
  float centerY;
  float windowWidth;
  float windowHeight;
  int radius;
  float speedX;
  float speedY;

public:
  Ball (){}
  void init (float, float, int);
  bool move(float);
  void normalizeSpeed();
  void collideWall();
  void setWindowSize(float, float);
  bool didCollidePaddle(Paddle paddle);
  float getLeftX();
  float getRightX();
  float getUpperY();
  float getLowerY();
  float getCenterX();
  float getCenterY();
  float getSpeedX();
  float getSpeedY();
  int getRadius();
};

#endif
