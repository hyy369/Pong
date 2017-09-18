#ifndef PADDLE_H
#define PADDLE_H

class Paddle
{
private:
  float x;
  float y;
  float windowHeight;
  int width;
  int length;
  int side; //left = 0, right = 1;

public:
  Paddle (){}
  void init (float, float, int, int, int);
  void moveUp(int);
  void moveDown(int);
  void setX(float);
  void setWindowHeight(float);
  float getLeftX();
  float getRightX();
  float getUpperY();
  float getCenterY();
  float getLowerY();
  int getWidth();
  int getLength();
  int getSide();
};

#endif
