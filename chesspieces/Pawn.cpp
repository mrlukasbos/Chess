//
// Created by Lukas Bos on 04/12/2017.
//

#include <iostream>
#include "Pawn.h"

Pawn::Pawn(Board *board, GridElement *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = PAWN;
    generateImage(type);
}

std::vector<GridElement *> Pawn::getAvailableMoves(bool considerOtherPieces) {
    std::vector<GridElement *> availableMoves;

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

        bool elementExists = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;
        if (elementExists) {
            GridElement *element = board->elements[xLocation][yLocation];
            if (!considerOtherPieces || (element->chessPiece && element->chessPiece->color != color)) {
                availableMoves.push_back(element);
            }
        }
    }

    if (!considerOtherPieces) {
        return availableMoves;
    }

    int maxAmountOfSteps = hasMoved ? 1 : 2;

    for (int i = 0; i < maxAmountOfSteps; i++) {
        int yLocation = y + (direction * pawnDirections[i].y); // reverse ydirection for other color

        // no need to check for x; we do not change it
        bool elementExists = yLocation >= 0 && yLocation < 8;
        if (elementExists) {
            GridElement *element = board->elements[x][yLocation];

            if (!element->chessPiece) {
                availableMoves.push_back(element);
            }
        }
    }

    return availableMoves;
}