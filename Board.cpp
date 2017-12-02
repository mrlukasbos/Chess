//
// Created by Lukas Bos on 30/11/2017.
//

#include "Board.h"
#include "constants.h"

using namespace sf;

Board::Board(sf::RenderWindow& window) : window(window) {

    for (short i  = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            Color color = (j + i) % 2 == 1 ? Color(100, 100, 100) : Color::White;

            char letters[8] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
            std::string name = letters[i] + std::to_string(8 - j);
            elements[i][j] = GridElement(i * BLOCK_SIZE, j * BLOCK_SIZE, BLOCK_SIZE, color, name);
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
    elements[0][0].setChessPiece(new Rook(WHITE, &elements[0][0]));
    elements[7][0].setChessPiece(new Rook(WHITE, &elements[7][0]));

    elements[0][7].setChessPiece(new Rook(BLACK, &elements[0][7]));
    elements[7][7].setChessPiece(new Rook(BLACK, &elements[7][7]));

}

void Board::selectGridElement(int x, int y) {
    for (short i  = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            GridElement * element = &elements[i][j];
            element->setSelected(false); // there should be no other elements be selected.

            if (x > element->posX && x < element->posX+BLOCK_SIZE
                    && y > element->posY && y < element->posY+BLOCK_SIZE) {
                element->setSelected(true);

                selectedGridElement = element;

            }
        }
    }
}

