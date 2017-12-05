//
// Created by Lukas Bos on 04/12/2017.
//

#include "Queen.h"

Queen::Queen(Board *board, GridElement *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = QUEEN;
    generateImage(type);
}

std::vector<GridElement *> Queen::getAvailableMoves() {

    Vector2i allDirections[] = {
            Vector2i(0, 1),   // Down
            Vector2i(1, 0),   // Right
            Vector2i(0, -1),  // Up
            Vector2i(-1, 0),  // Left
            Vector2i(1, 1),   // Right-Down
            Vector2i(1, -1),  // Right-Up
            Vector2i(-1, -1), // Left-Up
            Vector2i(-1, 1)   // Left-Down
    };

    return calculateMovesForDirections(location, allDirections, board, color, 8, 7);
}