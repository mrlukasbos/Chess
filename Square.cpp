// Created by Lukas Bos on 30/11/2017.

#include "Square.h"

Square::Square() {}

Square::Square(int x, int y, int size, sf::Color color, sf::Vector2i coordinates)
        : posX(x), posY(y), size(size), color(color), coordinates(coordinates) {

    char letters[] = "abcdefgh";
    name = letters[coordinates.x] + std::to_string(8 - coordinates.y);
}

void Square::drawSquare(sf::RenderWindow &window) {

    rectangle.setPosition(posX + SELECTION_LINE_THICKNESS, posY + SELECTION_LINE_THICKNESS);
    rectangle.setSize(sf::Vector2f(size - 2*SELECTION_LINE_THICKNESS, size - 2*SELECTION_LINE_THICKNESS));
    rectangle.setOutlineThickness(SELECTION_LINE_THICKNESS);

    if (isSelected) {
        rectangle.setOutlineColor(sf::Color::Blue);
    } else if (isFocused && chessPiece) {
        rectangle.setOutlineColor(sf::Color::Red);
    } else if (isFocused) {
        rectangle.setOutlineColor(sf::Color::Green);
    } else if (isChecked) {
        rectangle.setOutlineColor(sf::Color::Yellow);
    } else {
        rectangle.setOutlineColor(color);
    }

    rectangle.setFillColor(color);
    window.draw(rectangle);

    if (chessPiece) {
        chessPiece->drawChessPiece(window);
    }
}

void Square::setSelected(bool selected) {
    this->isSelected = selected;
}

void Square::setFocused(bool focused) {
    this->isFocused = focused;
}

void Square::setChessPiece(ChessPiece *piece) {
    chessPiece = piece;
}
