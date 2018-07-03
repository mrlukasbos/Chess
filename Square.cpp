// Created by Lukas Bos on 30/11/2017.

#include "Square.h"

using namespace sf;
using namespace std;

Square::Square(Vector2i coordinates) : coordinates(coordinates) {
    char letters[] = "abcdefgh";
    this->name = letters[coordinates.x] + to_string(8 - coordinates.y);
}

string Square::getName() {
    return name;
}

void Square::setChessPiece(ChessPiece * piece) {
    this->chessPiece = piece;
}

ChessPiece* Square::getChessPiece() {
    return chessPiece;
}

void Square::removeChessPiece() {
    this->chessPiece = nullptr;
}

Vector2i Square::getCoordinates() {
    return coordinates;
}
