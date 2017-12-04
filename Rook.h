//
// Created by Lukas Bos on 04/12/2017.
//

#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H


#include "ChessPiece.h"

class Rook : public ChessPiece {
public:
    Rook(Board *board, GridElement *location, PieceColor color, PieceType type);

};


#endif //CHESS_ROOK_H
