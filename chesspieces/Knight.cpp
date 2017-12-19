//
// Created by Lukas Bos on 04/12/2017.
//

#include "Knight.h"

Knight::Knight(Board *board, GridElement *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = KNIGHT;
    generateImage(type);

    pieceScore = KNIGHT_SCORE;

    locationScores = {{
                              {-50, -40, -30, -30, -30, -30, -40, -50},
                              {-40, -20, 0, 0, 0, 0, -20, -40},
                              {-30, 0, 10, 15, 15, 10, 0, -30},
                              {-30, 5, 15, 20, 20, 15, 5, -30},
                              {-30, 0, 15, 20, 20, 15, 0, -30},
                              {-30, 5, 10, 15, 15, 10, 5, -30},
                              {-40, -20, 0, 5, 5, 0, -20, -40},
                              {-50, -40, -30, -30, -30, -30, -40, -50}
                      }};
}

std::vector<GridElement *> Knight::getAvailableMoves(bool considerOtherPieces) {
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

    return calculateMovesForDirections(location, knightDirections, board, color, 8, 1, considerOtherPieces);
}