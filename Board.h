//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "GridElement.h"
#include "chesspieces/Rook.h"
#include <SFML/Graphics.hpp>

class Board {
public:
    Board();
    GridElement elements[8][8];
    void drawBoard(sf::RenderWindow &window);
    Rook whiteRook;
    void startGame();

};


#endif //CHESS_BOARD_H
