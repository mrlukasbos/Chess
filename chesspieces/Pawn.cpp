//
// Created by Lukas Bos on 04/12/2017.
//

#include <iostream>
#include "Pawn.h"

Pawn::Pawn(Board *board, Square *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = PAWN;
    generateImage(type);

    pieceScore = PAWN_SCORE;

    locationScores = {{
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {50, 50, 50, 50, 50, 50, 50, 50},
                              {10, 10, 20, 30, 30, 20, 10, 10},
                              {5, 5, 10, 25, 25, 10, 5, 5},
                              {0, 0, 0, 20, 20, 0, 0, 0},
                              {5, -5, -10, 0, 0, -10, -5, 5},
                              {5, 10, 10, -20, -20, 10, 10, 5},
                              {0, 0, 0, 0, 0, 0, 0, 0}
                      }};
}

std::vector<Square *> Pawn::getAvailableMoves(bool considerOtherPieces, bool considerCheck) {
    std::vector<Square *> availableMoves;

    short y = location->coordinates.y;
    short x = location->coordinates.x;

    bool isBottomColor = board->bottomPlayer->color == color;
    short direction = isBottomColor ? -1 : 1;

    Vector2i pawnDirections[] = {
            Vector2i(0, 1),
            Vector2i(0, 2),
    };

    // capturing works differently for pawns...
    Vector2i pawnCaptureDirections[]{
            Vector2i(1, 1),
            Vector2i(-1, 1),
    };

    // there are 2 directions
    for (short i = 0; i < 2; i++) {
        int xLocation = x + pawnCaptureDirections[i].x;
        int yLocation = y + (direction * pawnCaptureDirections[i].y); // reverse ydirection for other color

        bool squareExists = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;
        if (squareExists) {
            Square *square = board->squares[xLocation][yLocation];
            if (!considerOtherPieces || (square->chessPiece && square->chessPiece->color != color)) {
                availableMoves.push_back(square);
            }
        }
    }

//    if (!considerOtherPieces) {
//        return removeMovesLeadingToSelfCheck(availableMoves);
//    }

    int maxAmountOfSteps = (amountOfSteps > 0) ? 1 : 2;

    for (int i = 0; i < maxAmountOfSteps; i++) {
        int yLocation = y + (direction * pawnDirections[i].y); // reverse ydirection for other color

        // no need to check for x; we do not change it
        bool squareExists = yLocation >= 0 && yLocation < 8;
        if (squareExists) {
            Square *square = board->squares[x][yLocation];

            if (square->chessPiece) {
                break;
            }
            availableMoves.push_back(square);

        }
    }

    if (considerCheck) {
        return removeMovesLeadingToSelfCheck(availableMoves);
    }
    return availableMoves;
}