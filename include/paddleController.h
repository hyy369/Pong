#ifndef PADDLECONTROLLER_H
#define PADDLECONTROLLER_H

#include "../include/paddle.h"
#include "../include/ball.h"

class PaddleController
{
private:
  Paddle *paddle;

public:
  PaddleController (Paddle &);
  void init (Paddle &);
  void makeDecision (Ball &, int);
};

#endif
