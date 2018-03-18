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


std::vector<Move *> King::getAvailableMoves(bool considerCheck) {

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

    std::vector<Move *> moves;

    int y = location->coordinates.y;
    int x = location->coordinates.x;

    // At this part we get all the directions where the king may initially go
    for (int i = 0; i < 8; i++) {
        int xLocation = x + (allDirections[i].x);
        int yLocation = y + (allDirections[i].y);

        bool squareShouldExist = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;

        if (squareShouldExist) {
            Square *square = board->squares[xLocation][yLocation];
            bool squareHasFriendlyPiece = square->chessPiece && square->chessPiece->color == color;

            if (!squareHasFriendlyPiece) {
                Move *move  = new Move(board, location, square);
                moves.push_back(move);
            }
        }

    }

    moves = addCastlingMoves(moves, considerCheck);

    if (considerCheck) {
        return removeMovesLeadingToSelfCheck(moves);
    }
    return moves;
}

std::vector<Move *> King::addCastlingMoves(std::vector<Move *> moves, bool considerCheck) {
    if (amountOfSteps == 0) {

        // first try to the right (kingside castling)
        for (int i = 1; i <= 3; i++) {
            Square * neighbourSquare = board->squares[location->coordinates.x + i][location->coordinates.y];
            if (i <= 2) {
                // castling not allowed when piece in between
                if (neighbourSquare->chessPiece) break;

                if (considerCheck) {
                    // check if positions 1 and 2 have check
                    bool positionsBetweenHasCheck = false;
                    for (ChessPiece *piece : board->getPiecesByColor(inverse(color))) {
                        for (Move *move : piece->getAvailableMoves(false)) {
                            if (move->endOfMove == neighbourSquare) {
                                positionsBetweenHasCheck = true;
                            }
                        }
                    }
                    if (positionsBetweenHasCheck) break;
                }
            }
            else if (i == 3) {
               if (neighbourSquare->chessPiece->type == ROOK && neighbourSquare->chessPiece->amountOfSteps == 0) {
                   Move *move = new Move(board, location, board->squares[location->coordinates.x + 2][location->coordinates.y]);

                   // add some castling rule and/or indication here...

                   moves.push_back(move);
               }
            }
        }
    }
    return moves;
}

