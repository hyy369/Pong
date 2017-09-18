#ifndef PONG_H
#define PONG_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main(int argc, char** argv);
void playPaddleSound();
void playWallSound();
void initGame(Paddle &, Paddle &, Ball &);

#endif
