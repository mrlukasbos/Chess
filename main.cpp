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

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Interface.h"
#include "players/HumanPlayer.h"
#include "players/MinMaxPlayer.h"
#include "players/RandomPlayer.h"

using namespace sf;

int main() {
  ContextSettings settings;
  settings.antialiasingLevel = 8;
  RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Chess", Style::Default, settings);
  window.setFramerateLimit(40);

  Board board = Board();
  Interface interface(&board, window);
  Player *topPlayer = new MinMaxPlayer(PieceColor::WHITE, 6);
  Player *bottomPlayer = new MinMaxPlayer(PieceColor::BLACK, 1);

  // white begins
  Player *currentPlayer = bottomPlayer->getColor()==PieceColor::WHITE ? bottomPlayer : topPlayer;
  board.startGame(bottomPlayer, topPlayer, currentPlayer);

  while (window.isOpen()) {

    Event event;
    while (window.pollEvent(event)) {
      // Handle Events
      if (event.type==Event::Closed) {
        window.close();
      } else if (event.type==Event::MouseButtonPressed) {
        if (currentPlayer->isHuman) {
          currentPlayer->setNextMove(interface.getHumanMove());
        }
      } else if (event.type==Event::KeyPressed) {
        if (Keyboard::isKeyPressed(Keyboard::R)) { // humanplayer plays as White
          board.undoMove();
        }
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

        interface.draw();
        window.display();
      }
  }
}