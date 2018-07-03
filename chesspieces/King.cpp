//
// Created by Lukas Bos on 04/12/2017.
//

#include <iostream>
#include "King.h"
#include "../PieceColor.h"

King::King(Board *board, Square *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = KING;
    pieceScore = KING_SCORE;
    locationScores = {{
        {{-30, -40, -40, -50, -50, -40, -40, -30}},
        {{-30, -40, -40, -50, -50, -40, -40, -30}},
        {{-30, -40, -40, -50, -50, -40, -40, -30}},
        {{-30, -40, -40, -50, -50, -40, -40, -30}},
        {{-20, -30, -30, -40, -40, -30, -30, -20}},
        {{-10, -20, -20, -20, -20, -20, -20, -10}},
        {{20,   20,   0,   0,   0,   0,  20,  20}},
        {{20,   30,  10,   0,   0,  10,  30,  20}}
    }};
}


std::vector<Square *> King::getAvailableSquares(bool considerCheck) {

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

    std::vector<Square *> squares;

    int y = location->getCoordinates().y;
    int x = location->getCoordinates().x;

    // At this part we get all the directions where the king may initially go
    for (int i = 0; i < 8; i++) {
        int xLocation = x + (allDirections[i].x);
        int yLocation = y + (allDirections[i].y);

        bool squareShouldExist = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;

        if (squareShouldExist) {
            Square *square = board->getSquare(xLocation, yLocation);
            bool squareHasFriendlyPiece = square->getChessPiece() && square->getChessPiece()->color == color;

            if (!squareHasFriendlyPiece) {
                squares.push_back(square);
            }
        }

    }
    
    if (considerCheck) {
        return removeMovesLeadingToSelfCheck(squares);
    }
    return squares;
}

std::vector<Move *> King::getAvailableMoves(bool considerCheck) {
    std::vector<Move *> moves;
    for (Square * square : getAvailableSquares(considerCheck)) {
        moves.push_back(new Move(board, location, square));
    }
    return addCastlingMoves(moves, considerCheck);
}

std::vector<Move *> King::addCastlingMoves(std::vector<Move *> moves, bool considerCheck) {
    
    if (amountOfSteps == 0 && (considerCheck && !board->isInCheck(color))) {
        int directions[] = {-1, 1};
        
        CastlingSide castlingSides[] = {CastlingSide::QUEENSIDE, CastlingSide::KINGSIDE};
        
        for (int i = 0; i < 2; i++) {
            int castleAllowed = true;
            ChessPiece * castlingRook;
            // 1 to 4 positions to the sides
            for (int j = 1; j<=4; j++) {
                int neighbourXLocation = location->getCoordinates().x + j * directions[i];
                if (neighbourXLocation < 0 || neighbourXLocation > 7) continue; // don't look for squares outside the board
                
                Square * neighbour = board->getSquare(neighbourXLocation, location->getCoordinates().y);
                
                
                // check the corner squares for a legal rook
                if (neighbourXLocation == 0 || neighbourXLocation == 7) {
                    if ((neighbour->getChessPiece()) && (neighbour->getChessPiece()->type == ROOK) && (neighbour->getChessPiece()->amountOfSteps == 0))  {
                        castlingRook = neighbour->getChessPiece();
                    } else {
                        castleAllowed = false;
                    }
                } else { // not at a corner square
                    if (neighbour->getChessPiece()) castleAllowed = false;
                }
                
                // At this point there is a king and a rook that has not moved and the squares between the king and rook are empty.
                if (considerCheck) {
                    // check if the two positions next
                    if (j <= 2) {
                        Move * moveToTry = new Move(board, location, neighbour, true);
                        board->doMove(moveToTry);
                        if (board->isInCheck(color)) castleAllowed = false;
                        board->undoMove();
                    }
                }
            }
            
            if (castleAllowed && castlingRook) {
                Square * kingTargetSquare = board->getSquare(location->getCoordinates().x + (2 * directions[i]), location->getCoordinates().y);
                Square * rookTargetSquare = board->getSquare(location->getCoordinates().x + (1 * directions[i]), location->getCoordinates().y);
                moves.push_back(new Move(board, location, kingTargetSquare, false, castlingSides[i], castlingRook, castlingRook->location, rookTargetSquare));
            }
        }
    }
    return moves;
}
