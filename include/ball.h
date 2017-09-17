#ifndef BALL_H
#define BALL_H

class Ball
{
private:
  float centerX;
  float centerY;
  float leftX;
  float rightX;
  float upperY;
  float lowerY;
  int radius;
  float speedX;
  float speedY;

public:
  Ball (){}
  void init (float, float, int);
  void move();
  void reflect();
  void updateEdges();
  float getLeftX();
  float getUpperY();
  float getSpeedX();
  float getSpeedY();
  int getRadius();
};

#endif
