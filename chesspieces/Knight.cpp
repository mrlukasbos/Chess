//
// Created by Lukas Bos on 04/12/2017.
//

#include "Knight.h"

Knight::Knight(Board *board, GridElement *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = KNIGHT;
    generateImage(type);
}