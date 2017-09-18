#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Audio.hpp>
#include "../include/paddle.h"
#include "../include/ball.h"
#include "../include/paddleController.h"
#include "../include/pong.h"

sf::Font font;
// sf::Sound hitWallSound;
// sf::Sound hitPaddleSound;
// sf::SoundBuffer hitWallSoundBuffer;
// sf::SoundBuffer hitPaddleSoundBuffer;

int main(int argc, char** argv)
{
  //Font file is downloaded from https://github.com/todylu/monaco.ttf/blob/master/monaco.ttf
  if (!font.loadFromFile("../monaco.ttf"))
  {
    // error
    std::cout << "Error loading font file." << std::endl;
  }

  sf::Sound hitWallSound;
  sf::Sound hitPaddleSound;
  sf::SoundBuffer hitWallSoundBuffer;
  sf::SoundBuffer hitPaddleSoundBuffer;
  if (!hitWallSoundBuffer.loadFromFile("../resources/hitWall.ogg"))
  {
    //error
    std::cout << "Error loading sound file." << std::endl;
  }

  if (!hitPaddleSoundBuffer.loadFromFile("../resources/hitPaddle.ogg"))
  {
    // error
    std::cout << "Error loading sound file." << std::endl;
  }

  hitWallSound.setBuffer(hitWallSoundBuffer);
  hitPaddleSound.setBuffer(hitPaddleSoundBuffer);


  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "The Pong Game");

  int playerScore = 0;
  int AIScore = 0;
  int paddleLength = 100;
  int paddleWidth = 5;
  int ballRadius = 10;
  srand (time(NULL));

  Paddle AIPaddle;
  Paddle playerPaddle;
  Ball ball;
  AIPaddle.init(50,250,paddleWidth,paddleLength,0);
  playerPaddle.init(750,250,paddleWidth,paddleLength,1);
  ball.init(400,300,ballRadius);

  PaddleController AIController(AIPaddle);

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

  sf::Text messageText;
  messageText.setFont(font);
  messageText.setCharacterSize(24);
  messageText.setFillColor(sf::Color::White);
  messageText.setPosition(200,250);


  //start main game loop
  while (App.isOpen())
  {
    // process events
    sf::Event Event;
    while(App.pollEvent(Event))
    {
      // Exit
      if(Event.type == sf::Event::Closed)
        App.close();
    }

    // start round loop
    while(playerScore < 11 && AIScore < 11)
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

      if (ball.move())
      {
        hitWallSound.play();
      }
      if (ball.didCollidePaddle(AIPaddle))
      {
        hitPaddleSound.play();
      }
      if (ball.didCollidePaddle(playerPaddle))
      {
        hitPaddleSound.play();
      }
      AIController.makeDecision(ball);

      if (ball.getLeftX() <= 0.0) {
        playerScore++;
        // std::cout << "Player scores.\n";
        AIPaddle.init(50,250,paddleWidth,paddleLength,0);
        playerPaddle.init(750,250,paddleWidth,paddleLength,1);
        ball.init(400,300,ballRadius);
      } else if (ball.getRightX() >= 800.0) {
        AIScore++;
        // std::cout << "AI scores.\n";
        AIPaddle.init(50,250,paddleWidth,paddleLength,0);
        playerPaddle.init(750,250,paddleWidth,paddleLength,1);
        ball.init(400,300,ballRadius);
      }

      // clear screen and fill with black
      App.clear(sf::Color::Black);

      AIPaddleShape.setPosition(AIPaddle.getLeftX(),AIPaddle.getUpperY());
      playerPaddleShape.setPosition(playerPaddle.getLeftX(),playerPaddle.getUpperY());
      ballShape.setPosition(ball.getLeftX(),ball.getUpperY());
      App.draw(ballShape);
      App.draw(AIPaddleShape);
      App.draw(playerPaddleShape);

      scoreText.setString("Computer  " +
                          std::to_string(AIScore) + " : " +
                          std::to_string(playerScore) + "  Player");
      App.draw(scoreText);


      //Display ball movement information for debugging
      debugText.setString("ballX: " +
                          std::to_string(ball.getLeftX()) + " ballY: " +
                          std::to_string(ball.getUpperY()) + " speedX: " +
                          std::to_string(ball.getSpeedX()) + " speedY: " +
                          std::to_string(ball.getSpeedY()));
      App.draw(debugText);

      // display
      App.display();
    }

    //display winner message
    App.clear(sf::Color::Black);
    if (AIScore == 11)
    {
      messageText.setString("Computer wins! Restart Game?\n  Press Y/N");
    } else {
      messageText.setString("You win! Restart Game?\n  Press Y/N");
    }
    App.draw(messageText);
    App.display();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
    {
      playerScore = 0;
      AIScore = 0;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
    {
      App.close();
    }

  }

  // Done.
  return 0;
}

void playPaddleSound ()
{
  // sf::Sound hitPaddleSound;
  // hitPaddleSound.setBuffer(hitPaddleSoundBuffer);
  // hitPaddleSound.play();
}

void playWallSound ()
{
  // sf::Sound hitWallSound;
  // hitWallSound.setBuffer(hitWallSoundBuffer);
  // hitWallSound.play();
}

void initGame (Paddle &AIPaddle, Paddle &playerPaddle, Ball &ball)
{
  // AIPaddle -> init(50,250,paddleWidth,paddleLength,0);
  // playerPaddle -> init(750,250,paddleWidth,paddleLength,1);
  // ball -> init(400,300,ballRadius);
}
