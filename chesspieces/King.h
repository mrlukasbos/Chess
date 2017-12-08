//
// Created by Lukas Bos on 04/12/2017.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "../ChessPiece.h"

class King : public ChessPiece {
public:
    King(Board *board, GridElement *location, PieceColor color);

    std::vector<GridElement *> getAvailableMoves();

    std::vector<GridElement *> getAvailableMovesWithCheck();
};


#endif //CHESS_KING_H
