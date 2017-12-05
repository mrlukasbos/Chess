//
// Created by Lukas Bos on 04/12/2017.
//

#include "Knight.h"

Knight::Knight(Board *board, GridElement *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = KNIGHT;
    generateImage(type);
}

std::vector<GridElement *> Knight::getAvailableMoves() {
    std::vector<GridElement *> availableMoves;

    Vector2i knightDirections[] = {
            Vector2i(-2, 1),
            Vector2i(-2, -1),
            Vector2i(-1, 2),
            Vector2i(-1, -2),
            Vector2i(1, 2),
            Vector2i(1, -2),
            Vector2i(2, 1),
            Vector2i(2, -1)
    };

    return calculateMovesForDirections(location, knightDirections, board, color, 8, 1);
}