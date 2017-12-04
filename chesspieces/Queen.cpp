//
// Created by Lukas Bos on 04/12/2017.
//

#include "Queen.h"

Queen::Queen(Board *board, GridElement *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = QUEEN;
    generateImage(type);
}