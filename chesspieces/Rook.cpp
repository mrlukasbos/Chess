//
// Created by Lukas Bos on 04/12/2017.
//

#include "Rook.h"

Rook::Rook(Board *board, GridElement *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = ROOK;
    generateImage(type);

    pieceScore = ROOK_SCORE;

    locationScores = {{
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {5, 10, 10, 10, 10, 10, 10, 5},
                              {-5, 0, 0, 0, 0, 0, 0, -5},
                              {-5, 0, 0, 0, 0, 0, 0, -5},
                              {-5, 0, 0, 0, 0, 0, 0, -5},
                              {-5, 0, 0, 0, 0, 0, 0, -5},
                              {-5, 0, 0, 0, 0, 0, 0, -5},
                              {0, 0, 0, 5, 5, 0, 0, 0}
                      }};
}

std::vector<GridElement *> Rook::getAvailableMoves(bool considerOtherPieces, bool considerCheck) {

    Vector2i horizontalAndVerticalDirections[] = {
            Vector2i(0, 1),  // Down
            Vector2i(1, 0),  // Right
            Vector2i(0, -1), // Up
            Vector2i(-1, 0)  // Left
    };

    return calculateMovesForDirections(location, horizontalAndVerticalDirections, board, color, 4, 7,
                                       considerOtherPieces, considerCheck);
}