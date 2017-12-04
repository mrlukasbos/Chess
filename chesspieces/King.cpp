//
// Created by Lukas Bos on 04/12/2017.
//

#include "King.h"

King::King(Board *board, GridElement *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = KING;
    generateImage(type);
}