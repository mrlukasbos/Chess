//
// Created by Lukas Bos on 04/12/2017.
//

#include <iostream>
#include "King.h"

King::King(Board *board, Square *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = KING;
    generateImage(type);

    pieceScore = KING_SCORE;

    locationScores = {{
                              {-30, -40, -40, -50, -50, -40, -40, -30},
                              {-30, -40, -40, -50, -50, -40, -40, -30},
                              {-30, -40, -40, -50, -50, -40, -40, -30},
                              {-30, -40, -40, -50, -50, -40, -40, -30},
                              {-20, -30, -30, -40, -40, -30, -30, -20},
                              {-10, -20, -20, -20, -20, -20, -20, -10},
                              {20, 20, 0, 0, 0, 0, 20, 20},
                              {20, 30, 10, 0, 0, 10, 30, 20}
                      }};
}


std::vector<Square *> King::getAvailableMoves(bool considerOtherPieces, bool considerCheck) {

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

    std::vector<Square *> moves;

    short y = location->coordinates.y;
    short x = location->coordinates.x;


    // --- at this part we get all the directions where the king may initially go
    for (int i = 0; i < 8; i++) {
        for (short j = 1; j <= 1; j++) {
            short xLocation = x + (j * allDirections[i].x);
            short yLocation = y + (j * allDirections[i].y);

            bool squareShouldExist = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;

            if (squareShouldExist) {
                Square *square = board->squares[xLocation][yLocation];
                if (square->chessPiece && square->chessPiece->color == color) {
                    break;
                } else if (square->chessPiece) {
                    moves.push_back(square);
                    break;
                }
                moves.push_back(square);
            }
        }
    }

    return removeMovesLeadingToSelfCheck(moves, considerCheck);

}
