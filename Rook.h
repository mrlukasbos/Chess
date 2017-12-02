//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H

#include "ChessPiece.h"
#include <iostream>

using namespace sf;

class Rook : public ChessPiece {
public:
    Rook(PieceColor color);

    std::string pieceName; // also used to generate imageUrl
};


#endif //CHESS_ROOK_H
