//
// Created by Lukas Bos on 30/11/2017.
//

#include "Rook.h"


Rook::Rook(PieceColor color) : ChessPiece(color) {

    pieceName = "Rook";
    img.loadFromFile("images/" + imageUrlPrefix + pieceName + ".png");

}
