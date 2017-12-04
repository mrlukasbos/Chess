//
// Created by Lukas Bos on 04/12/2017.
//

#include "Bishop.h"

Bishop::Bishop(Board *board, GridElement *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = BISHOP;
    generateImage(type);
}