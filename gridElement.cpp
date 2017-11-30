//
// Created by Lukas Bos on 30/11/2017.
//

#include "GridElement.h"

GridElement::GridElement() { }

GridElement::GridElement(int x, int y, int size, sf::Color color) {
    this->posX = x;
    this->posY = y;
    this->size = size;
    this->color = color;

    rectangle.setPosition(posX, posY);
    rectangle.setSize(sf::Vector2f(size, size));
    rectangle.setFillColor(color);
}

