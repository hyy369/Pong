#ifndef PADDLE_H
#define PADDLE_H

class Paddle
{
private:
  float x;
  float y;
  int length;

public:
  Paddle (){}
  void init (float, float, int);
  void moveUp();
  void moveDown();
  float getX();
  float getY();
  int getLength();
};

#endif
