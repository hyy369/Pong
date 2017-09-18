#include "../include/paddle.h"
#include "../include/ball.h"
#include "../include/paddleController.h"

#include <iostream>

PaddleController::PaddleController(Paddle &paddle) {
  this -> paddle = &paddle;
  // std::cout << this -> paddle << "\n";
}

void PaddleController::init(Paddle &paddle)
{
  this -> paddle = &paddle;
}

void PaddleController::makeDecision (Ball &ball, int frameDelta)
{
  if (ball.getCenterY() < paddle -> getUpperY())
  {
    paddle -> moveUp(frameDelta);
    // std::cout << "Move up paddle\n";
  } else if (ball.getUpperY() > paddle -> getLowerY()) {
    paddle -> moveDown(frameDelta);
    // std::cout << "Move down paddle\n";
  }
}
