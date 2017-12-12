//
// Created by Lukas Bos on 04/12/2017.
//

#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H


#include "../ChessPiece.h"

class Rook : public ChessPiece {
public:
    Rook(Board *board, GridElement *location, PieceColor color);

    std::vector<GridElement *> getAvailableMoves(bool considerOtherPieces);

    int locationScores[64] = {
            0, 0, 0, 0, 0, 0, 0, 0,
            5, 10, 10, 10, 10, 10, 10, 5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            0, 0, 0, 5, 5, 0, 0, 0
    };
};


#endif //CHESS_ROOK_H
