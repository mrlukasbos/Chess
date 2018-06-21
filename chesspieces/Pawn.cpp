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
        {{0,   0,   0,   0,   0,   0,   0,  0}},
        {{50, 50,  50,  50,  50,  50,  50, 50}},
        {{10, 10,  20,  30,  30,  20,  10, 10}},
        {{5,   5,  10,  25,  25,  10,   5,  5}},
        {{0,   0,   0,  20,  20,   0,   0,  0}},
        {{5,  -5, -10,   0,   0, -10,  -5,  5}},
        {{5,  10,  10, -20, -20,  10,  10,  5}},
        {{0,   0,   0,   0,   0,   0,   0,  0}}
    }};
}

vector<Move *> Pawn::getAvailableMoves(bool considerCheck) {
    std::vector<Move *> moves;
    for (Square * square : getAvailableSquares(considerCheck)) {
        
        Move * move = new Move(board, location, square);
        // when a pawn reaches bottom or top it can promote
        if (square->coordinates.y == 7 || square->coordinates.y == 0) {
            move->isPromoting = true;
        }
        moves.push_back(move);
    }
    return addEnPassantMoves(moves);
}


vector<Square *> Pawn::getAvailableSquares(bool considerCheck) {
    std::vector<Square *> availableMoves;

    int y = location->coordinates.y;
    int x = location->coordinates.x;

    bool isBottomColor = board->bottomPlayer->color == color;
    int direction = isBottomColor ? -1 : 1;

    Vector2i pawnDirections[] = {
            Vector2i(0, 1),
            Vector2i(0, 2),
    };

    Vector2i pawnCaptureDirections[]{
            Vector2i(1, 1),
            Vector2i(-1, 1),
    };

    // 2 directions
    for (int i = 0; i < 2; i++) {
        int xLocation = x + pawnCaptureDirections[i].x;
        int yLocation = y + (direction * pawnCaptureDirections[i].y); // reverse ydirection for other color

        bool squareExists = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;
        if (squareExists) {
            Square *square = board->squares[xLocation][yLocation];
            if (square->chessPiece && square->chessPiece->color != color) {
                availableMoves.push_back(square);
            }
        }
    }

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

vector<Move *> Pawn::addEnPassantMoves(vector<Move *> moves) {
    Move * previousMove = board->allMoves.back();

    if (board->allMoves.size() > 0 && previousMove && previousMove->initialPiece->type == PieceType::PAWN) {
        ChessPiece *opponentPawn = previousMove->initialPiece;
        Vector2i loc = this->location->coordinates;
        Vector2i opLoc = opponentPawn->location->coordinates;
        if (loc.y == opLoc.y && (((loc.x + 1) == opLoc.x) || (loc.x - 1) == opLoc.x)) {
            bool movedTwoSquaresFromBottom = opLoc.y == 3;
            bool movedTwoSquaresFromTop = opLoc.y == 4;
            if (opponentPawn->amountOfSteps == 1) {
                if (movedTwoSquaresFromBottom) {
                    Move * enPassantMove = new Move(board, this->location, board->squares[opLoc.x][2]);
                    enPassantMove->enPassantTakenPiece = opponentPawn;
                    moves.push_back(enPassantMove);
                } else if (movedTwoSquaresFromTop) {
                    Move * enPassantMove = new Move(board, this->location, board->squares[opLoc.x][5]);
                    enPassantMove->enPassantTakenPiece = opponentPawn;
                    moves.push_back(enPassantMove);
                }
            }
        }
    }
    return moves;
}
