#ifndef PADDLE_H
#define PADDLE_H

class Paddle
{
private:
  int x;
  int y;
  int length;

public:
  Paddle (){}
  void init (int, int, int);
  void moveUp();
  void moveDown();
  int getX();
  int getY();
  int getLength();
};

#endif
