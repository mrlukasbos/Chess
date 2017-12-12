//
// Created by Lukas Bos on 04/12/2017.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include "../ChessPiece.h"

class Bishop : public ChessPiece {
public:
    Bishop(Board *board, GridElement *location, PieceColor color);

    std::vector<GridElement *> getAvailableMoves(bool considerOtherPieces);

    int pieceScore = BISHOP_SCORE;

    int locationScores[64] = {
            -20, -10, -10, -10, -10, -10, -10, -20,
            -10, 0, 0, 0, 0, 0, 0, -10,
            -10, 0, 5, 10, 10, 5, 0, -10,
            -10, 5, 5, 10, 10, 5, 5, -10,
            -10, 0, 10, 10, 10, 10, 0, -10,
            -10, 10, 10, 10, 10, 10, 10, -10,
            -10, 5, 0, 0, 0, 0, 5, -10,
            -20, -10, -10, -10, -10, -10, -10, -20,
    };
};


#endif //CHESS_BISHOP_H
