//
// Created by Lukas Bos on 30/11/2017.
//

#include "Board.h"


Board::Board() {
    const short BLOCK_SIZE = 100;
    for (short i  = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            sf::Color color = (j+i)%2 == 1 ? sf::Color::Black : sf::Color::White;
            elements[i][j] = GridElement(i * BLOCK_SIZE, j*BLOCK_SIZE, BLOCK_SIZE, color);
        }
    }
}

void Board::drawBoard(sf::RenderWindow &window) {
    //draw the gridElements
    for (short i  = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            window.draw(elements[i][j].rectangle);
        }
    }
}
