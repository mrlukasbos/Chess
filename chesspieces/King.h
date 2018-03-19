//
// Created by Lukas Bos on 04/12/2017.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "../ChessPiece.h"

class King : public ChessPiece {
public:
    King(Board *board, Square *location, PieceColor color);

    std::vector<Square *> getAvailableMoves(bool considerCheck);
};


#endif //CHESS_KING_H
