// Created by Lukas Bos on 04/12/2017.

#include "Bishop.h"

Bishop::Bishop(Board *board, Square *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = BISHOP;
    pieceScore = BISHOP_SCORE;
    locationScores = {{
        {{-20, -10, -10, -10, -10, -10, -10, -20}},
        {{-10,   0,   0,   0,   0,   0,   0, -10}},
        {{-10,   0,   5,  10,  10,   5,   0, -10}},
        {{-10,   5,   5,  10,  10,   5,   5, -10}},
        {{-10,   0,  10,  10,  10,  10,   0, -10}},
        {{-10,  10,  10,  10,  10,  10,  10, -10}},
        {{-10,   5,   0,   0,   0,   0,   5, -10}},
        {{-20, -10, -10, -10, -10, -10, -10, -20}}
    }};
}

std::vector<Square *> Bishop::getAvailableSquares(bool considerCheck) {
    Vector2i diagonalDirections[] = {
            Vector2i(1, 1),   // Right-Down
            Vector2i(1, -1),  // Right-Up
            Vector2i(-1, -1), // Left-Up
            Vector2i(-1, 1)   // Left-Down
    };
    return calculateMovesForDirections(location, diagonalDirections, board, color, 4, 7, considerCheck);
}
