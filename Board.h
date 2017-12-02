//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "GridElement.h"
#include "Rook.h"
#include <SFML/Graphics.hpp>

class Board {
public:
    Board(sf::RenderWindow& window);
    GridElement elements[8][8];
    void drawBoard();

    // Rook whiteRook;
    void startGame();

    void selectGridElementFromMousePos(int x, int y);

    void selectGridElementFromCoordinates(sf::Vector2i coordinates);

    GridElement * selectedGridElement;
private:
    sf::RenderWindow& window;

};


#endif //CHESS_BOARD_H
