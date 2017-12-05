//
// Created by Lukas Bos on 30/11/2017.
//

#include "Board.h"
#include "chesspieces/Rook.h"
#include "chesspieces/Bishop.h"
#include "chesspieces/Knight.h"
#include "chesspieces/Pawn.h"
#include "chesspieces/Queen.h"
#include "chesspieces/King.h"

using namespace sf;

Board::Board(sf::RenderWindow& window) : window(window) {
    createBoard();
}

void Board::drawBoard() {
    for (short i  = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            elements[i][j]->drawGridElement(window);
        }
    }
}

// set all pieces to the initial position
void Board::startGame(PieceColor bottomColor, PieceColor topColor) {
    createBoard();

    this->bottomColor = bottomColor;
    this->topColor = topColor;

    playerToMove = bottomColor;

    short kingXPosition = 3, queenXPosition = 4;
    if (topColor == BLACK) {
        kingXPosition = 4;
        queenXPosition = 3;
    }

    // make all pieces twice
    for (int i = 0; i < 2; i++) {
        PieceColor color = topColor;
        short row = 0;

        if (i == 1) {
            color = bottomColor;
            row = 7;
        }

        elements[0][row]->setChessPiece(new Rook(this, elements[0][row], color));
        elements[1][row]->setChessPiece(new Knight(this, elements[1][row], color));
        elements[2][row]->setChessPiece(new Bishop(this, elements[2][row], color));
        elements[queenXPosition][row]->setChessPiece(new Queen(this, elements[queenXPosition][row], color));
        elements[kingXPosition][row]->setChessPiece(new King(this, elements[kingXPosition][row], color));
        elements[5][row]->setChessPiece(new Bishop(this, elements[5][row], color));
        elements[6][row]->setChessPiece(new Knight(this, elements[6][row], color));
        elements[7][row]->setChessPiece(new Rook(this, elements[7][row], color));
    }

    // add pawns
    for (int i = 0; i < 8; i++) {
        elements[i][1]->setChessPiece(new Pawn(this, elements[i][1], topColor));
        elements[i][6]->setChessPiece(new Pawn(this, elements[i][6], bottomColor));
    }
}

//TODO add player implementation
void Board::selectGridElementFromMousePos(int x, int y) {
    for (short i  = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            GridElement *element = elements[i][j];
            element->setSelected(false); // there should be no other elements be selected.

            if (x > element->posX && x < element->posX + BLOCK_SIZE
                && y > element->posY && y < element->posY + BLOCK_SIZE) {
                // now we have the clicked element


                // when we click on a focused element
                if (element->isFocused && !element->chessPiece) {
                    //move the piece to there

                    element->chessPiece = selectedGridElement->chessPiece;
                    element->chessPiece->location = element;
                    element->chessPiece->hasMoved = true;
                    selectedGridElement->chessPiece = NULL;

                    switchPlayer();
                } else if (element->isFocused) { //let's capture a piece!
                    element->chessPiece->isCaptured = true;

                    // set the piece that has captured to other to the position
                    element->chessPiece = selectedGridElement->chessPiece;
                    element->chessPiece->location = element;
                    element->chessPiece->hasMoved = true;
                    switchPlayer();
                } else {
                    // if a piece of the current player is selected
                    if (element->chessPiece && element->chessPiece->color == playerToMove) {

                        element->setSelected(true);
                        selectedGridElement = element;
                    }
                }



            }
        }
    }

    focusGridElements();
}

void Board::selectGridElementFromCoordinates(sf::Vector2i coordinates) {
    selectedGridElement->setSelected(false); // set selected property of previous element to false
    selectedGridElement = elements[(coordinates.x)][coordinates.y];
    selectedGridElement->setSelected(true); // set new element to selected

    focusGridElements();
}

void Board::focusGridElements() {
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            elements[i][j]->setFocused(false); // there should be no other elements be selected.
        }
    }

    // here check for the elements where the selected element may move to
    if (selectedGridElement && selectedGridElement->chessPiece) {
        std::vector<GridElement *> availableMoves = selectedGridElement->chessPiece->getAvailableMoves();

        for (int i = 0; i < availableMoves.size(); i++) {
            availableMoves.at(i)->setFocused(true);
        }
    }
}

void Board::createBoard() {
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            Color color = (j + i) % 2 == 1 ? Color(100, 100, 100) : Color::White;

            sf::Vector2i coordinates = sf::Vector2i(i, j);
            elements[i][j] = new GridElement(i * BLOCK_SIZE, j * BLOCK_SIZE, BLOCK_SIZE, color, coordinates);
        }
    }
}

void Board::switchPlayer() {
    if (playerToMove == BLACK) {
        playerToMove = WHITE;
    } else {
        playerToMove = BLACK;
    }
}
