//
// Created by Lukas Bos on 04/12/2017.
//

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H


#include "ChessPiece.h"

class Knight : public ChessPiece {
public:
    Knight(Board *board, GridElement *location, PieceColor color, PieceType type);

};


#endif //CHESS_KNIGHT_H
