//
// Created by Lukas Bos on 04/12/2017.
//

#include "Pawn.h"

Pawn::Pawn(Board *board, GridElement *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = PAWN;
    generateImage(type);
}