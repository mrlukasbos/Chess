//
// Created by Lukas Bos on 30/11/2017.
//

#include "GridElement.h"
#include <iostream>
#include <stdio.h>

GridElement::GridElement() {

}


GridElement::GridElement(int x, int y, int size) {
    this->posX = x;
    this->posY = y;
    this->size = size;

    rectangle.setPosition(posX, posY);
    rectangle.setSize(sf::Vector2f(size, size));

printf("posX: %d \t %d \t %d \n", posX, posY, size);
    rectangle.setFillColor(sf::Color::White);
}

