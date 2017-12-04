//
// Created by Lukas Bos on 04/12/2017.
//

#include "Rook.h"

Rook::Rook(Board *board, GridElement *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = ROOK;
    generateImage(type);
}