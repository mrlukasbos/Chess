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

class ChessPiece;
class Move;
class Board {
public:
    Board(RenderWindow &window);
    GridElement *elements[8][8];
    void drawBoard();
    void startGame(Player *bottomPlayer, Player *topPlayer);
    void selectGridElementFromCoordinates(Vector2i coordinates);
    void focusGridElements();
    GridElement * selectedGridElement;
    Player *bottomPlayer;
    Player *topPlayer;
    Player *currentPlayer;
    RenderWindow &window;

    std::vector<ChessPiece *> getPiecesByColor(PieceColor color);
private:
    void createBoard();
    void switchPlayer();
    void drawPiecesOnBoard();
    void doMove();


};


#endif //CHESS_BOARD_H
