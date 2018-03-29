// Created by Lukas Bos on 04/12/2017.

#include "Queen.h"

Queen::Queen(Board *board, Square *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = QUEEN;
    generateImage(type);
    pieceScore = QUEEN_SCORE;
    locationScores = {{
        {{-20, -10, -10, -5, -5, -10, -10, -20}},
        {{-10, 0, 0, 0, 0, 0, 0, -10}},
        {{-10, 0, 5, 5, 5, 5, 0, -10}},
        {{-5, 0, 5, 5, 5, 5, 0, -5}},
        {{0, 0, 5, 5, 5, 5, 0, -5}},
        {{-10, 5, 5, 5, 5, 5, 0, -10}},
        {{-10, 0, 5, 0, 0, 0, 0, -10}},
        {{-20, -10, -10, -5, -5, -10, -10, -20}}
    }};
}

std::vector<Square *> Queen::getAvailableMoves(bool considerCheck) {
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
    return calculateMovesForDirections(location, allDirections, board, color, 8, 7, considerCheck);
}
