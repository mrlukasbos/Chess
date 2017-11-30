//
// Created by Lukas Bos on 30/11/2017.
//

#include "GridElement.h"
#include <iostream>

GridElement::GridElement(int x, int y, int size) {
    this->posX = x;
    this->posY = y;
    this->size = size;

    rectangle.setPosition(posX, posY);
    rectangle.setSize(sf::Vector2f(size, size));
    std::cout << size;

    rectangle.setFillColor(sf::Color::White);
}
