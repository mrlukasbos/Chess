//
// Created by Lukas Bos on 16/03/2018.
//

#include "PieceColor.h"

PieceColor inverse(PieceColor const& color) {
    if (color == PieceColor::BLACK) {
        return PieceColor::WHITE;
    }
    return PieceColor::BLACK;
}