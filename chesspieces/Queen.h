//
// Created by Lukas Bos on 04/12/2017.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "../ChessPiece.h"

class Queen : public ChessPiece {
public:
    Queen(Board *board, GridElement *location, PieceColor color);

    std::vector<GridElement *> getAvailableMoves(bool considerOtherPieces);
};


#endif //CHESS_QUEEN_H
