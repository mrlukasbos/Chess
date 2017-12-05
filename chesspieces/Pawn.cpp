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

    //TODO disable double jump when other piece is in the way
    //TODO add diagonal capture of pieces

    short y = location->coordinates.y;
    short x = location->coordinates.x;

    bool isBottomColor = board->bottomColor == color;
    short direction = isBottomColor ? -1 : 1;
    availableMoves.push_back(board->elements[x][y + (1 * direction)]);
    if (!hasMoved) {
        availableMoves.push_back(
                board->elements[x][y + (2 * direction)]);
    }
    return availableMoves;
}