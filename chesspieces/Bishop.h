//
// Created by Lukas Bos on 04/12/2017.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include "../ChessPiece.h"

class Bishop : public ChessPiece {
public:
    Bishop(Board *board, Square *location, PieceColor color);

    std::vector<Square *> getAvailableMoves(bool considerCheck) override;
};


#endif //CHESS_BISHOP_H
