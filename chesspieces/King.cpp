//
// Created by Lukas Bos on 04/12/2017.
//

#include <iostream>
#include "King.h"
#include "../PieceColor.h"

King::King(Board *board, Square *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = KING;
    generateImage(type);
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


std::vector<Square *> King::getAvailableMoves(bool considerCheck) {

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
                moves.push_back(square);
            }
        }

    }

    moves = addCastlingMoves(moves, considerCheck);
    
    if (considerCheck) {
        return removeMovesLeadingToSelfCheck(moves);
    }
    return moves;
}

std::vector<Square *> King::addCastlingMoves(std::vector<Square *> squares, bool considerCheck) {
    
    if (amountOfSteps == 0 && (considerCheck && !board->isInCheck(color))) {
        int directions[] = {-1, 1};
        
        // this will be an enum later.
        std::string castleNames[] = {"Queenside", "Kingside"};
        
        
        for (int i = 0; i < 2; i++) {
            
            int castleAllowed = true;
            // 1 to 4 positions to the sides
            for (int j = 1; j<=4; j++) {
                int neighbourXLocation = location->coordinates.x + j * directions[i];
                if (neighbourXLocation < 0 || neighbourXLocation > 7) continue; // don't look for squares outside the board
                
                Square * neighbour = board->squares[neighbourXLocation][location->coordinates.y];
                
                
                // the outer squares must have a rook that did not move.
                if ((neighbourXLocation == 0 || neighbourXLocation == 7)
                    && (!neighbour->chessPiece
                        || neighbour->chessPiece->type != ROOK
                        || neighbour->chessPiece->amountOfSteps > 0))  {
                    castleAllowed = false;
                } else if (neighbour->chessPiece && !(neighbourXLocation == 0 || neighbourXLocation == 7)) castleAllowed = false;
                
//                std::cout << "allowed? " << castleAllowed << " direction: " << castleNames[i] + " move: " << j << " \n";
                
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
            
            if (castleAllowed) {
                squares.push_back(board->squares[location->coordinates.x + (2 * directions[i])][location->coordinates.y]);
            }
        }
    }
    return squares;
}
