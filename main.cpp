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
#include "players/HumanPlayer.h"
#include "players/MinMaxPlayer.h"
#include "Interface.h"

using namespace sf;

int main() {
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Chess", Style::Default, settings);
    window.setFramerateLimit(20);

    Board board = Board();
    Interface interface(&board, window);
    Player *bottomPlayer = new HumanPlayer(PieceColor::BLACK);
    Player *topPlayer = new MinMaxPlayer(PieceColor::WHITE);

    // white begins
    Player * currentPlayer = bottomPlayer->color == PieceColor::WHITE ? bottomPlayer : topPlayer;
    board.startGame(bottomPlayer, topPlayer, currentPlayer);

    bool isSetup = false;

    while(window.isOpen()) {

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }


            //draw interface once
            if (!isSetup) {
                interface.draw();
                isSetup = true;
            }

            //    board.handleEvent(interface.getLastEvent());
            Move *nextMove = currentPlayer->getNextMove(&board);
            if (nextMove) {
                board.doMove(nextMove);
                board.checkGameStatus();

                // switch player after move
                if (currentPlayer == topPlayer) {
                    currentPlayer = bottomPlayer;
                } else {
                    currentPlayer = topPlayer;
                }
                board.setCurrentPlayer(currentPlayer);
                interface.draw();
            }
        }
        window.display();
    }
}


//
//
////start interface
//    while (window.isOpen()) {
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed) {
//                window.close();
//            }
//
//            if (event.type != Event::MouseMoved) {
//            // use keys to set window modi.
//            // When having a humanplayer it is recommended to make the human the bottomplayer
//
//            if (Keyboard::isKeyPressed(Keyboard::W)) { // humanplayer plays as White
//                Player *bottomPlayer = new HumanPlayer(PieceColor::WHITE, window);
//                Player *topPlayer = new MinMaxPlayer(PieceColor::BLACK);
//                board.startGame(bottomPlayer, topPlayer, currentPlayer);
//
//            } else if (Keyboard::isKeyPressed(Keyboard::B)) {  // humanplayer plays as Black
//                Player *bottomPlayer = new HumanPlayer(PieceColor::BLACK, window);
//                Player *topPlayer = new MinMaxPlayer(PieceColor::WHITE);
//                board.startGame(bottomPlayer, topPlayer, currentPlayer);
//            } else if (Keyboard::isKeyPressed(Keyboard::R)) {
//                board.undoMove();
//                board.checkGameStatus();
//            }
//
//            // update screen after event.
//                drawNextMoveOnBoard(window, currentPlayer, interface, board);
//            }
//        }
//
//        Move *nextMove = currentPlayer->getNextMove(&board);
//        if (nextMove) {
//            board.doMove(nextMove);
//            board.checkGameStatus();
//
//            // switch player after move
//            if (currentPlayer == topPlayer) {
//                currentPlayer = bottomPlayer;
//            } else {
//                currentPlayer = topPlayer;
//            }
//            board.setCurrentPlayer(currentPlayer);
//
//            drawNextMoveOnBoard(window, currentPlayer, interface, board);
//            if (!currentPlayer->isHuman) {
//                interface.showLoadingText();
//            }
//
//            // the computer may have done a move so we want to update the screen.
//            updateWindowNextCycle = true;
//        }
//
//        interface.display();

