//
// Created by Lukas Bos on 30/11/2017.
//

#include "Board.h"
#include "constants.h"

Board::Board(sf::RenderWindow& window) : window(window) {

    for (short i  = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            sf::Color color = (j+i)%2 == 1 ? sf::Color::Black : sf::Color::White;
            elements[i][j] = GridElement(i * BLOCK_SIZE, j * BLOCK_SIZE, BLOCK_SIZE, color);
        }
    }
}

void Board::drawBoard() {
    //draw the gridElements
    for (short i  = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
           elements[i][j].drawGridElement(window);
        }
    }
}

// set all pieces to the initial position
void Board::startGame() {

}

void Board::selectGridElement(int x, int y) {
    for (short i  = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            GridElement * element = &elements[i][j];
            element->setSelected(false); // there should be no other elements be selected.

            if (x > element->posX && x < element->posX+BLOCK_SIZE
                    && y > element->posY && y < element->posY+BLOCK_SIZE) {
                element->setSelected(true);
                char letters[8] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
                printf("Clicked %c%d \n", letters[i], j+1);
            }
        }
    }
}
