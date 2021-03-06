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
  if (!font.loadFromFile("../resources/monaco.ttf"))
    std::cout << "Error loading font file." << std::endl;

  //Init sound system
  //Sound effects are from iMovie library
  sf::Sound hitWallSound;
  sf::Sound hitPaddleSound;
  sf::Sound scoreUpSound;
  sf::SoundBuffer hitWallSoundBuffer;
  sf::SoundBuffer hitPaddleSoundBuffer;
  sf::SoundBuffer scoreUpSoundBuffer;
  if (!hitWallSoundBuffer.loadFromFile("../resources/hitWall.ogg"))
    std::cout << "Error loading sound file." << std::endl;
  if (!hitPaddleSoundBuffer.loadFromFile("../resources/hitPaddle.ogg"))
    std::cout << "Error loading sound file." << std::endl;
  if (!scoreUpSoundBuffer.loadFromFile("../resources/scoreUp.ogg"))
    std::cout << "Error loading sound file." << std::endl;
  hitWallSound.setBuffer(hitWallSoundBuffer);
  hitPaddleSound.setBuffer(hitPaddleSoundBuffer);
  scoreUpSound.setBuffer(scoreUpSoundBuffer);

  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "The Pong Game");

  //Init variables
  int playerScore = 0;
  int AIScore = 0;
  int paddleLength = 100;
  int paddleWidth = 5;
  int ballRadius = 10;
  float frameDelta = 0.0;
  int currWidth = 800;
  int currHeight = 600;
  float speedFactor = 0.8;  //default difficulty is normal
  enum GameStates {MENU, GAME, PAUSED, MESSAGE};  //game states to control game flow
  GameStates currState = MENU; //default state is start up menu
  GameStates savedState; //saved state when game paused
  sf::Event Event;
  srand (time(NULL)); //seed rng

  //Init Actors
  Paddle AIPaddle;
  Paddle playerPaddle;
  Ball ball;
  PaddleController AIController(AIPaddle);

  //Init shapes
  sf::RectangleShape AIPaddleShape(sf::Vector2f(paddleWidth,paddleLength));
  sf::RectangleShape playerPaddleShape(sf::Vector2f(paddleWidth,paddleLength));
  sf::CircleShape ballShape(ballRadius);
  ballShape.setFillColor(sf::Color::White);
  AIPaddleShape.setFillColor(sf::Color(sf::Color::White));
  playerPaddleShape.setFillColor(sf::Color(sf::Color::White));

  //Init Texts
  // sf::Text debugText;
  // debugText.setFont(font);
  // debugText.setCharacterSize(12);
  // debugText.setFillColor(sf::Color::White);
  // debugText.setPosition(0,0);

  sf::Text scoreText;
  scoreText.setFont(font);
  scoreText.setCharacterSize(24);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition(240,32);

  sf::Text messageText;
  messageText.setFont(font);
  messageText.setCharacterSize(24);
  messageText.setFillColor(sf::Color::White);
  messageText.setPosition(200,250);

  sf::Text menuText;
  menuText.setFont(font);
  menuText.setCharacterSize(24);
  menuText.setFillColor(sf::Color::White);
  menuText.setPosition(150,100);

  //Init clock
  sf::Clock clock;


  //start main game loop
  while (App.isOpen())
  {
    // process events
    while(App.pollEvent(Event))
    {
      // Exit
      switch (Event.type)
      {
        case sf::Event::Closed:
          App.close();
          break;
        case sf::Event::LostFocus:
          savedState = currState;
          currState = PAUSED;
          break;
        case sf::Event::GainedFocus:
          currState = savedState;
          clock.restart();
          break;
        case sf::Event::Resized:
          savedState = currState;
          currState = PAUSED;
          App.setView(sf::View(sf::FloatRect(0, 0, Event.size.width, Event.size.height)));
          currWidth = Event.size.width;
          currHeight = Event.size.height;
          playerPaddle.setWindowHeight(currHeight);
          AIPaddle.setWindowHeight(currHeight);
          ball.setWindowSize(currWidth,currHeight);
          playerPaddle.setX( (float)( currWidth - 50 ) );
          break;
        default:
          break;
      }
    }

    switch (currState)
    {
    //Display start up menu
    case MENU :
      //display menu
      App.clear(sf::Color::Blue);
      menuText.setString("Welcome come to the Pong game!\n\nPress keyboard to choose difficulty:\n1 = Easy\n2 = Normal\n3 = Hard\n\nYou control the paddle on the right.\nPress 'K' to move up and 'M' to move down.");
      App.draw(menuText);
      App.display();

      //Choose diffculty
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
      {
        speedFactor = 0.4;
        currState = GAME;
        AIPaddle.init(50,currHeight,paddleWidth,paddleLength,0);
        playerPaddle.init(currWidth-50,currHeight,paddleWidth,paddleLength,1);
        ball.init(currWidth,currHeight,ballRadius);
        clock.restart();
      } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
      {
        speedFactor = 0.7;
        currState = GAME;
        AIPaddle.init(50,currHeight,paddleWidth,paddleLength,0);
        playerPaddle.init(currWidth-50,currHeight,paddleWidth,paddleLength,1);
        ball.init(currWidth,currHeight,ballRadius);
        clock.restart();
      } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
      {
        speedFactor = 1.0;
        currState = GAME;
        AIPaddle.init(50,currHeight,paddleWidth,paddleLength,0);
        playerPaddle.init(currWidth-50,currHeight,paddleWidth,paddleLength,1);
        ball.init(currWidth,currHeight,ballRadius);
        clock.restart();
      }
      break;

    //main game logic
    case GAME:
      frameDelta = (float) clock.getElapsedTime().asMilliseconds();
      frameDelta *= speedFactor;
      clock.restart();

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
        scoreUpSound.play();
        // std::cout << "Player scores." << std::endl;
        AIPaddle.init(50,currHeight,paddleWidth,paddleLength,0);
        playerPaddle.init(currWidth-50,currHeight,paddleWidth,paddleLength,1);
        ball.init(currWidth,currHeight,ballRadius);
      } else if (ball.getRightX() >= currWidth) {
        AIScore++;
        scoreUpSound.play();
        // std::cout << "AI scores." << std::endl;
        AIPaddle.init(50,currHeight,paddleWidth,paddleLength,0);
        playerPaddle.init(currWidth-50,currHeight,paddleWidth,paddleLength,1);
        ball.init(currWidth,currHeight,ballRadius);
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
      // debugText.setString("ballX: " +
      //                     std::to_string(ball.getLeftX()) + " ballY: " +
      //                     std::to_string(ball.getUpperY()) + " speedX: " +
      //                     std::to_string(ball.getSpeedX()) + " speedY: " +
      //                     std::to_string(ball.getSpeedY()));
      // App.draw(debugText);

      // display
      App.display();
      // if one player wins, display message
      if (playerScore == 11 || AIScore == 11)
        currState = MESSAGE;
      break;

    //Display pause screen
    case PAUSED:
      App.clear(sf::Color(64,64,64));
      messageText.setString("Game is paused.\nFocus or press Enter (Return) to resume.");
      App.draw(messageText);
      App.display();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
      {
        currState = savedState;
        clock.restart();
      }
      break;

    //Start message loop
    case MESSAGE:
      //display winner message
      if (AIScore == 11)
      {
        App.clear(sf::Color::White);
        messageText.setFillColor(sf::Color::Black);
        messageText.setString("Computer wins! Restart Game?\nPress Y/N");
      }
      else
      {
        App.clear(sf::Color::Red);
        messageText.setString("You win! Restart Game?\n  Press Y/N");
      }
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
      break;
    } //end of switch
  } //end of while

  // Done.
  return 0;
}
