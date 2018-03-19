//
// Created by Lukas Bos on 04/12/2017.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "../ChessPiece.h"

class Queen : public ChessPiece {
public:
    Queen(Board *board, Square *location, PieceColor color);

    std::vector<Square *> getAvailableMoves(bool considerCheck);
};


#endif //CHESS_QUEEN_H
