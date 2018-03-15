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
    Board board;
    Player *bottomPlayer = new HumanPlayer(WHITE, window);
    Player *topPlayer = new MinMaxPlayer(BLACK);
    board.startGame(bottomPlayer, topPlayer);
    Player *currentPlayer;
    Interface interface(window, board);

    // white begins
    currentPlayer = bottomPlayer->color == WHITE ? bottomPlayer : topPlayer;

    //start interface
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            Color menuColor(220, 220, 220); // light gray
            window.clear(menuColor);

            Move *nextMove = currentPlayer->getNextMove(board);
            if (nextMove) {
                board.doMove(nextMove);
                board.checkGameStatus();

                // switch player after move
                if (currentPlayer == topPlayer) {
                    currentPlayer = bottomPlayer;
                } else {
                    currentPlayer = topPlayer;
                }
            }

            interface.showBoardBackground();

            board.drawBoard(window); // this is where the redraw of the board happens

            // use keys to set window modi.
            // When having a humanplayer it is recommended to make the human the bottomplayer

            if (sf::Keyboard::isKeyPressed(Keyboard::W)) { // humanplayer plays as White
                Player *bottomPlayer = new HumanPlayer(WHITE, window);
                Player *topPlayer = new MinMaxPlayer(BLACK);
                board.startGame(bottomPlayer, topPlayer);

            } else if (Keyboard::isKeyPressed(Keyboard::B)) {  // humanplayer plays as Black
                Player *bottomPlayer = new HumanPlayer(BLACK, window);
                Player *topPlayer = new MinMaxPlayer(WHITE);
                board.startGame(bottomPlayer, topPlayer);
            } else if (Keyboard::isKeyPressed(Keyboard::R)) {
                board.undoMove();
                board.checkGameStatus();
            }

            interface.showCurrentPlayerText(currentPlayer);
            interface.showSelectedSquareName();
            interface.showPlayerTypes();
            interface.showCoordinates();

            window.display();
        }
    }
    return 0;
}
