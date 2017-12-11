//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "GridElement.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Player;
class GridElement;

class Move;
class Board {
public:
    Board(RenderWindow &window);

    GridElement *elements[8][8];

    void drawBoard();

    void startGame(Player *bottomPlayer, Player *topPlayer);
    void selectGridElementFromMousePos(int x, int y);
    void selectGridElementFromCoordinates(Vector2i coordinates);

    GridElement * selectedGridElement;

    Player *bottomPlayer;
    Player *topPlayer;
    Player *currentPlayer;

private:
    RenderWindow &window;
    void focusGridElements();
    void createBoard();
    void switchPlayer();
    void drawPiecesOnBoard();

    void doMove();

    Move *nextMove = NULL;
};


#endif //CHESS_BOARD_H
