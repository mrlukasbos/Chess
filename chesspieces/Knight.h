//
// Created by Lukas Bos on 04/12/2017.
//

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H


#include "../ChessPiece.h"

class Knight : public ChessPiece {
public:
    Knight(Board *board, Square *location, PieceColor color);

    std::vector<Square *> getAvailableMoves(bool considerOtherPieces, bool considerCheck);
};


#endif //CHESS_KNIGHT_H
