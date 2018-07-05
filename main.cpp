/*
 * CHESS
 * This game is created to explore algorithms and C++ in general.
 * It is mainly a project to gain experience and understanding in these topics,
 * so it probably won't be the best chess program.
 *
 * main.cpp
 * Created by Lukas Bos on 30/11/2017.
 * Initialize a board and the players and handle the immediate user input
 * Initialize a proper interface for the player/viewer
 * 
*/

#include "Board.h"
#include "players/HumanPlayer.h"
#include "players/MinMaxPlayer.h"
#include "Interface.h"

using namespace sf;
using namespace tgui;

int main() {
  ContextSettings settings;
  settings.antialiasingLevel = 8;
  RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Chess", Style::Default, settings);
  window.setFramerateLimit(40);

  Gui gui{window};


  Board board = Board();
  Interface interface(&board, window);
  Player *bottomPlayer = new HumanPlayer(PieceColor::BLACK);
  Player *topPlayer = new MinMaxPlayer(PieceColor::WHITE);

  // white begins
  Player *currentPlayer = bottomPlayer->getColor()==PieceColor::WHITE ? bottomPlayer : topPlayer;
  board.startGame(bottomPlayer, topPlayer, currentPlayer);

  while (window.isOpen()) {

    Event event;
    while (window.pollEvent(event)) {

      gui.handleEvent(event); // Pass the event to the widgets

      // Handle Events
      if (event.type==Event::Closed) {
        window.close();
      } else if (event.type==Event::MouseButtonPressed) {
        if (currentPlayer->isHuman) {
          currentPlayer->setNextMove(interface.getHumanMove());
        }
      } else if (event.type==Event::KeyPressed) {

        if (Keyboard::isKeyPressed(Keyboard::W)) {
          Player *bottomPlayer = new HumanPlayer(PieceColor::WHITE);
          Player *topPlayer = new MinMaxPlayer(PieceColor::BLACK);
          currentPlayer = bottomPlayer->getColor()==PieceColor::WHITE ? bottomPlayer : topPlayer;
          board.startGame(bottomPlayer, topPlayer, currentPlayer);
        }

        if (Keyboard::isKeyPressed(Keyboard::B)) {
          Player *bottomPlayer = new HumanPlayer(PieceColor::BLACK);
          Player *topPlayer = new MinMaxPlayer(PieceColor::WHITE);
          currentPlayer = bottomPlayer->getColor()==PieceColor::WHITE ? bottomPlayer : topPlayer;
          board.startGame(bottomPlayer, topPlayer, currentPlayer);
        }

        if (Keyboard::isKeyPressed(Keyboard::R)) {
          board.undoMove();
        }
      }

      Move *nextMove = currentPlayer->getNextMove(&board);
      if (nextMove) {
        board.doMove(nextMove);
        board.checkGameStatus();

        // remove the move from the player so it won't be tried again next time.
        currentPlayer->setNextMove(nullptr);
        interface.selectedSquare = nullptr;
        // switch player after move
        if (currentPlayer==topPlayer) {
          currentPlayer = bottomPlayer;
        } else {
          currentPlayer = topPlayer;
        }
        board.setCurrentPlayer(currentPlayer);
      }
    }
    window.clear(sf::Color(100, 100, 100));
    gui.draw(); // Draw all widgets
    interface.draw();
    window.display();
  }
}