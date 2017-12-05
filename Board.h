//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "GridElement.h"
#include <SFML/Graphics.hpp>


class GridElement;
class Board {
public:
    Board(sf::RenderWindow& window);

    GridElement *elements[8][8];
    void drawBoard();

    void startGame(PieceColor bottomColor, PieceColor topColor);

    void selectGridElementFromMousePos(int x, int y);

    void selectGridElementFromCoordinates(sf::Vector2i coordinates);

    GridElement * selectedGridElement;

    PieceColor bottomColor;
    PieceColor topColor;
    PieceColor playerToMove = WHITE;

private:
    sf::RenderWindow& window;

    void focusGridElements();

    void createBoard();

    void switchPlayer();
};


#endif //CHESS_BOARD_H
