//
// Created by Lukas Bos on 04/12/2017.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "../ChessPiece.h"

class Pawn : public ChessPiece {
public:
    Pawn(Board *board, Square *location, PieceColor color);

    std::vector<Square *> getAvailableSquares(bool considerCheck);
};

#endif //CHESS_PAWN_H
