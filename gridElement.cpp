//
// Created by Lukas Bos on 30/11/2017.
//

#include "GridElement.h"

GridElement::GridElement() { }

GridElement::GridElement(int x, int y, int size, sf::Color color)
        : posX(x), posY(y), size(size), color(color) {
}

void GridElement::drawGridElement(sf::RenderWindow &window) {
    rectangle.setPosition(posX, posY);
    rectangle.setSize(sf::Vector2f(size, size));

    if (isSelected) {
        rectangle.setFillColor(sf::Color::Magenta);
    } else {
        rectangle.setFillColor(color);
    }
    window.draw(rectangle);
    chessPiece.drawChessPiece(window);
}

void GridElement::setSelected(bool selected) {
    this->isSelected = selected;
}

