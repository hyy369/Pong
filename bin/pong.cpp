#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "../include/paddle.h"
#include "../include/ball.h"
#include "../include/paddleController.h"
#include "../include/pong.h"


int main(int argc, char** argv)
{
  //Init font
  sf::Font font;
  //Font file is downloaded from https://github.com/todylu/monaco.ttf/blob/master/monaco.ttf
  if (!font.loadFromFile("../monaco.ttf"))
  {
    // error
    std::cout << "Error loading font file." << std::endl;
  }

  //Init sound system
  sf::Sound hitWallSound;
  sf::Sound hitPaddleSound;
  sf::SoundBuffer hitWallSoundBuffer;
  sf::SoundBuffer hitPaddleSoundBuffer;
  if (!hitWallSoundBuffer.loadFromFile("../resources/hitWall.ogg"))
    std::cout << "Error loading sound file." << std::endl;
  if (!hitPaddleSoundBuffer.loadFromFile("../resources/hitPaddle.ogg"))
    std::cout << "Error loading sound file." << std::endl;
  hitWallSound.setBuffer(hitWallSoundBuffer);
  hitPaddleSound.setBuffer(hitPaddleSoundBuffer);

  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "The Pong Game");

  //Init variables
  int playerScore = 0;
  int AIScore = 0;
  int paddleLength = 100;
  int paddleWidth = 5;
  int ballRadius = 10;
  int frameDelta = 0;
  float speedFactor = 0.8;
  enum GameStates {MENU, GAME, MESSAGE};
  GameStates currState = MENU;
  sf::Event Event;
  srand (time(NULL));

  //Init Actors
  Paddle AIPaddle;
  Paddle playerPaddle;
  Ball ball;
  AIPaddle.init(50,250,paddleWidth,paddleLength,0);
  playerPaddle.init(750,250,paddleWidth,paddleLength,1);
  ball.init(400,300,ballRadius);
  PaddleController AIController(AIPaddle);

  //Init shapes
  sf::RectangleShape AIPaddleShape(sf::Vector2f(paddleWidth,paddleLength));
  sf::RectangleShape playerPaddleShape(sf::Vector2f(paddleWidth,paddleLength));
  sf::CircleShape ballShape(ballRadius);
  ballShape.setFillColor(sf::Color::White);
  AIPaddleShape.setFillColor(sf::Color(sf::Color::White));
  playerPaddleShape.setFillColor(sf::Color(sf::Color::White));

  //Init Texts
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

  sf::Text menuText;
  menuText.setFont(font);
  menuText.setCharacterSize(24);
  menuText.setFillColor(sf::Color::White);
  menuText.setPosition(200,250);

  //Init clock
  sf::Clock clock;


  //start main game loop
  while (App.isOpen())
  {
    // process events
    // sf::Event Event;
    while(App.pollEvent(Event))
    {
      // Exit
      if(Event.type == sf::Event::Closed)
        App.close();
    }

    //Start menu loop
    while (currState == MENU && App.isOpen()) {
      // process events
      while(App.pollEvent(Event))
      {
        // Exit
        if(Event.type == sf::Event::Closed)
          App.close();
      }

      //display menu
      App.clear(sf::Color::Black);
      menuText.setString("Press keyboard to choose difficulty:\n1 = Easy\n2 = Normal\n3 = Hard\n");
      App.draw(menuText);
      App.display();

      //Choose diffculty
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
      {
        speedFactor = 0.8;
        currState = GAME;
      } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
      {
        speedFactor = 0.9;
        currState = GAME;
      } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
      {
        speedFactor = 1.0;
        currState = GAME;
      }
    }

    // start round loop
    clock.restart();
    while (playerScore < 11 && AIScore < 11 && App.isOpen())
    {

      frameDelta = (int) clock.getElapsedTime().asMilliseconds();
      frameDelta *= speedFactor;
      clock.restart();
      // process events
      // sf::Event Event;
      while(App.pollEvent(Event))
      {
        // Exit
        if(Event.type == sf::Event::Closed)
          App.close();
      }

      //Move paddle using keyboard control
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        playerPaddle.moveUp(frameDelta);
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        playerPaddle.moveDown(frameDelta);

      //Move the ball and see if ball collides with paddles
      if (ball.move(frameDelta))
        hitWallSound.play();
      if (ball.didCollidePaddle(AIPaddle))
        hitPaddleSound.play();
      if (ball.didCollidePaddle(playerPaddle))
        hitPaddleSound.play();

      //Notify AIController to make decision
      AIController.makeDecision(ball,frameDelta);

      //Check if ball has hit opponent's edge
      if (ball.getLeftX() <= 0.0) {
        playerScore++;
        // std::cout << "Player scores." << std::endl;
        AIPaddle.init(50,250,paddleWidth,paddleLength,0);
        playerPaddle.init(750,250,paddleWidth,paddleLength,1);
        ball.init(400,300,ballRadius);
      } else if (ball.getRightX() >= 800.0) {
        AIScore++;
        // std::cout << "AI scores." << std::endl;
        AIPaddle.init(50,250,paddleWidth,paddleLength,0);
        playerPaddle.init(750,250,paddleWidth,paddleLength,1);
        ball.init(400,300,ballRadius);
      }

      //Update view
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

    //Start message loop
    currState = MESSAGE;
    while (currState == MESSAGE && App.isOpen())
    {
      // process events
      while(App.pollEvent(Event))
      {
        // Exit
        if(Event.type == sf::Event::Closed)
          App.close();
      }

      //display winner message
      App.clear(sf::Color::Black);
      if (AIScore == 11)
        messageText.setString("Computer wins! Restart Game?\n  Press Y/N");
      else
        messageText.setString("You win! Restart Game?\n  Press Y/N");
      App.draw(messageText);
      App.display();

      //Choose to restart game or quit
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
      {
        playerScore = 0;
        AIScore = 0;
        currState = MENU;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
      {
        App.close();
      }
    }

  }

  // Done.
  return 0;
}
