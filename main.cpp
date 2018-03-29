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

    Board board;
    Player *bottomPlayer = new HumanPlayer(PieceColor::WHITE, window);
    Player *topPlayer = new MinMaxPlayer(PieceColor::BLACK);
    board.startGame(bottomPlayer, topPlayer);
    
    Player *currentPlayer;
    Interface interface(window, board);
    Color menuColor(220, 220, 220); // light gray
    
    bool updateWindowNextCycle = false; // indicate if the window needs a refresh.

    // white begins
    currentPlayer = bottomPlayer->color == PieceColor::WHITE ? bottomPlayer : topPlayer;
    
    //start interface
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            
            if (event.type != sf::Event::MouseMoved || updateWindowNextCycle) {
            // use keys to set window modi.
            // When having a humanplayer it is recommended to make the human the bottomplayer
            
            if (sf::Keyboard::isKeyPressed(Keyboard::W)) { // humanplayer plays as White
                Player *bottomPlayer = new HumanPlayer(PieceColor::WHITE, window);
                Player *topPlayer = new MinMaxPlayer(PieceColor::BLACK);
                board.startGame(bottomPlayer, topPlayer);
                
            } else if (Keyboard::isKeyPressed(Keyboard::B)) {  // humanplayer plays as Black
                Player *bottomPlayer = new HumanPlayer(PieceColor::BLACK, window);
                Player *topPlayer = new MinMaxPlayer(PieceColor::WHITE);
                board.startGame(bottomPlayer, topPlayer);
            } else if (Keyboard::isKeyPressed(Keyboard::R)) {
                board.undoMove();
                board.checkGameStatus();
            }
                
            // update screen after event.
            window.clear(menuColor);
            interface.showBoardBackground();
            board.drawBoard(window); // this is where the redraw of the board happens
            interface.showCurrentPlayerText(currentPlayer);
            interface.showPlayerTypes();
            interface.showCoordinates();
            interface.showSelectedSquareName();
            updateWindowNextCycle = false;
            }
        }

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
            
            // the computer may have done a move so we want to update the screen.
            updateWindowNextCycle = true;
        }

        window.display();
    }
}

