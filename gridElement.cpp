//
// Created by Lukas Bos on 30/11/2017.
//

#include "GridElement.h"
#include "constants.h"

GridElement::GridElement() {}

GridElement::GridElement(int x, int y, int size, sf::Color color, std::string name)
        : posX(x), posY(y), size(size), color(color), name(name) {
}

void GridElement::drawGridElement(sf::RenderWindow &window) {

    rectangle.setPosition(posX + SELECTION_LINE_THICKNESS, posY + SELECTION_LINE_THICKNESS);
    rectangle.setSize(sf::Vector2f(size - 2*SELECTION_LINE_THICKNESS, size - 2*SELECTION_LINE_THICKNESS));
    rectangle.setOutlineThickness(SELECTION_LINE_THICKNESS);

    if (isSelected) {
        rectangle.setOutlineColor(sf::Color::Magenta);
    } else {
        rectangle.setOutlineColor(color);
    }

    rectangle.setFillColor(color);
    window.draw(rectangle);

    if (chessPiece) {
        chessPiece->drawChessPiece(window);
    }
}

void GridElement::setSelected(bool selected) {
    this->isSelected = selected;
}

void GridElement::setChessPiece(ChessPiece *piece) {
    chessPiece = piece;
}