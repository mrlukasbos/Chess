//
// Created by Lukas Bos on 04/12/2017.
//

#include "Bishop.h"

Bishop::Bishop(Board *board, GridElement *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = BISHOP;
    generateImage(type);
}

std::vector<GridElement *> Bishop::getAvailableMoves(bool considerOtherPieces) {

    Vector2i diagonalDirections[] = {
            Vector2i(1, 1),   // Right-Down
            Vector2i(1, -1),  // Right-Up
            Vector2i(-1, -1), // Left-Up
            Vector2i(-1, 1)   // Left-Down
    };
    return calculateMovesForDirections(location, diagonalDirections, board, color, 4, 7, considerOtherPieces);
}