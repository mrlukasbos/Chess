//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_GRIDELEMENT_H
#define CHESS_GRIDELEMENT_H

#include <SFML/Graphics.hpp>

class GridElement {

public:
    GridElement(int x, int y, int size);
    sf::RectangleShape rectangle;

private:
    int posX;
    int posY;
    int size;
};


#endif //CHESS_GRIDELEMENT_H
