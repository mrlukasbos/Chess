//
// Created by Lukas Bos on 30/11/2017.
//

#include "Board.h"

using namespace sf;

Board::Board(sf::RenderWindow& window) : window(window) {

    for (short i  = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            Color color = (j + i) % 2 == 1 ? Color(100, 100, 100) : Color::White;

            sf::Vector2i coordinates = sf::Vector2i(i, j);
            elements[i][j] = GridElement(i * BLOCK_SIZE, j * BLOCK_SIZE, BLOCK_SIZE, color, coordinates);
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

    // add all white pieces
    elements[0][0].setChessPiece(new ChessPiece(ROOK, WHITE, &elements[0][0]));
    elements[1][0].setChessPiece(new ChessPiece(KNIGHT, WHITE, &elements[1][0]));
    elements[2][0].setChessPiece(new ChessPiece(BISHOP, WHITE, &elements[2][0]));
    elements[3][0].setChessPiece(new ChessPiece(KING, WHITE, &elements[3][0]));
    elements[4][0].setChessPiece(new ChessPiece(QUEEN, WHITE, &elements[4][0]));
    elements[5][0].setChessPiece(new ChessPiece(BISHOP, WHITE, &elements[5][0]));
    elements[6][0].setChessPiece(new ChessPiece(KNIGHT, WHITE, &elements[6][0]));
    elements[7][0].setChessPiece(new ChessPiece(ROOK, WHITE, &elements[7][0]));

    // add white pawns
    for (int i = 0; i < 8; i++) {
        elements[i][1].setChessPiece(new ChessPiece(PAWN, WHITE, &elements[i][1]));
    }


    // Add black pawns
    for (int i = 0; i < 8; i++) {
        elements[i][6].setChessPiece(new ChessPiece(PAWN, BLACK, &elements[i][6]));
    }

    // Add black pieces
    elements[0][7].setChessPiece(new ChessPiece(ROOK, BLACK, &elements[0][7]));
    elements[1][7].setChessPiece(new ChessPiece(KNIGHT, BLACK, &elements[1][7]));
    elements[2][7].setChessPiece(new ChessPiece(BISHOP, BLACK, &elements[2][7]));
    elements[3][7].setChessPiece(new ChessPiece(KING, BLACK, &elements[3][7]));
    elements[4][7].setChessPiece(new ChessPiece(QUEEN, BLACK, &elements[4][7]));
    elements[5][7].setChessPiece(new ChessPiece(BISHOP, BLACK, &elements[5][7]));
    elements[6][7].setChessPiece(new ChessPiece(KNIGHT, BLACK, &elements[6][7]));
    elements[7][7].setChessPiece(new ChessPiece(ROOK, BLACK, &elements[7][7]));



}

void Board::selectGridElementFromMousePos(int x, int y) {
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

void Board::selectGridElementFromCoordinates(sf::Vector2i coordinates) {
    selectedGridElement->setSelected(false); // set selected property of previous element to false
    selectedGridElement = &elements[(coordinates.x)][coordinates.y];
    selectedGridElement->setSelected(true); // set new element to selected
}

