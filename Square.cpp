// Created by Lukas Bos on 30/11/2017.

#include "Square.h"

using namespace sf;
using namespace std;

Square::Square(Vector2i coordinates) : coordinates(coordinates) {
    char letters[] = "abcdefgh";
    this->name = letters[coordinates.x] + to_string(8 - coordinates.y);
}

void Square::setChessPiece(ChessPiece * piece) {
    this->chessPiece = piece;
}
