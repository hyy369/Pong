#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include "../include/paddle.h"
#include "../include/ball.h"

sf::Font font;

// sf::Text updateScoreText()
// {
//   sf::Text scoreText;
//   scoreText.setFont(font);
//   scoreText.setString("");
//   scoreText.setCharacterSize(32);
//   scoreText.setColor(sf::Color::White);
//   scoreText.setPosition(0,0);
// }


int main(int argc, char** argv)
{
  //Font file is downloaded from https://github.com/todylu/monaco.ttf/blob/master/monaco.ttf
  if (!font.loadFromFile("/Users/HYY/Documents/Workspace/Pong/monaco.ttf"))
  {
    // error
    std::cout << "Error loading font file.";
  }
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "The Pong Game");

  int playerScore = 0;
  int AIScore = 0;
  int paddleLength = 100;
  int paddleWidth = 5;
  int ballRadius = 10;

  Paddle AIPaddle;
  Paddle playerPaddle;
  Ball ball;
  AIPaddle.init(50,250,paddleWidth,paddleLength,0);
  playerPaddle.init(750,250,paddleWidth,paddleLength,1);
  ball.init(400,300,ballRadius);

  sf::RectangleShape AIPaddleShape(sf::Vector2f(paddleWidth,paddleLength));
  sf::RectangleShape playerPaddleShape(sf::Vector2f(paddleWidth,paddleLength));
  sf::CircleShape ballShape(ballRadius);
  ballShape.setFillColor(sf::Color::White);
  AIPaddleShape.setFillColor(sf::Color(sf::Color::White));
  playerPaddleShape.setFillColor(sf::Color(sf::Color::White));


  sf::Text debugText;
  debugText.setFont(font);
  debugText.setCharacterSize(12);
  debugText.setFillColor(sf::Color::White);
  debugText.setPosition(0,0);

  sf::Text scoreText;
  scoreText.setFont(font);
  scoreText.setCharacterSize(24);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition(100,32);

  // start main loop
  while(App.isOpen())
  {
    // process events
    sf::Event Event;
    while(App.pollEvent(Event))
    {
      // Exit
      if(Event.type == sf::Event::Closed)
        App.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
    {
      playerPaddle.moveUp();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
    {
      playerPaddle.moveDown();
    }

    ball.move();
    ball.checkCollidePaddle(AIPaddle);
    ball.checkCollidePaddle(playerPaddle);

    // clear screen and fill with black
    App.clear(sf::Color::Black);

    AIPaddleShape.setPosition(AIPaddle.getLeftX(),AIPaddle.getUpperY());
    playerPaddleShape.setPosition(playerPaddle.getLeftX(),playerPaddle.getUpperY());
    ballShape.setPosition(ball.getLeftX(),ball.getUpperY());
    App.draw(ballShape);
    App.draw(AIPaddleShape);
    App.draw(playerPaddleShape);

    // sf::Text scoreText = updateScoreText();
    debugText.setString("ballX: " +
                        std::to_string(ball.getLeftX()) + " ballY: " +
                        std::to_string(ball.getUpperY()) + " speedX: " +
                        std::to_string(ball.getSpeedX()) + " speeY: " +
                        std::to_string(ball.getSpeedY()));
    App.draw(debugText);

    scoreText.setString("Computer  " +
                        std::to_string(AIScore) + " : " +
                        std::to_string(playerScore) + "  Player");
    App.draw(scoreText);

    // display
    App.display();
  }


  // Done.
  return 0;
}
