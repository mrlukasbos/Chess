//
// Created by Lukas Bos on 04/12/2017.
//

#include "Pawn.h"

Pawn::Pawn(Board *board, GridElement *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = PAWN;
    generateImage(type);
}

std::vector<GridElement *> Pawn::getAvailableMoves() {
    std::vector<GridElement *> availableMoves;

    short y = location->coordinates.y;
    short x = location->coordinates.x;

    bool isBottomColor = board->bottomColor == color;
    short direction = isBottomColor ? -1 : 1;


    GridElement *oneForward = board->elements[x][y + (1 * direction)];
    GridElement *twoForward = board->elements[x][y + (2 * direction)];

    if (!oneForward->chessPiece) {
        availableMoves.push_back(oneForward);

        if (!twoForward->chessPiece && !hasMoved) {
            availableMoves.push_back(twoForward);
        }
    }


//    GridElement *diagonalup1 = board->elements[x + 1][y + (1 * direction)];
//    GridElement *diagonalup2 = board->elements[x - 1][y + (1 * direction)];
//
//    if (diagonalup1 && diagonalup1->chessPiece && diagonalup1->chessPiece->color != color) {
//        availableMoves.push_back(diagonalup1);
//    }
//
//    if (diagonalup2 && diagonalup2->chessPiece && diagonalup2->chessPiece->color != color) {
//        availableMoves.push_back(diagonalup2);
//    }
    return availableMoves;
}