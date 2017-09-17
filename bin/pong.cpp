#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include "../include/paddle.h"

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
  if (!font.loadFromFile("../monaco.ttf"))
  {
    // error
    std::cout << "Error loading font file.";
  }
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "The Pong Game");

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

    int playerScore = 0;
    int AIScore = 0;
    int paddleLength = 100;
    // while (playerScore < 10 && AIScore < 10)
    // {
      Paddle AIPaddle(50,250,paddleLength);
      Paddle playerPaddle(750,250,paddleLength);
      // clear screen and fill with black
      App.clear(sf::Color::Black);
      sf::RectangleShape AIPaddleShape(sf::Vector2f(5,paddleLength));
      sf::RectangleShape playerPaddleShape(sf::Vector2f(5,paddleLength));
      sf::CircleShape ballShape(15);
      ballShape.setFillColor(sf::Color::White);
      AIPaddleShape.setFillColor(sf::Color(255,255,255));
      playerPaddleShape.setFillColor(sf::Color(255,255,255));
      // AIPaddleShape.setPosition(AIPaddlet.getX(),AIPaddle.getY());
      // playerPaddleShape.setPosition(playerPaddle.getX(),playerPaddle.getY());
      ballShape.setPosition(385,285);
      AIPaddleShape.setPosition(50,250);
      playerPaddleShape.setPosition(750,250);
      App.draw(ballShape);
      App.draw(AIPaddleShape);
      App.draw(playerPaddleShape);

      // sf::Text scoreText = updateScoreText();
      // App.draw(scoreText);

      // display
      App.display();
    }
  // }

  // Done.
  return 0;
}
