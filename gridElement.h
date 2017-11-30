//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_GRIDELEMENT_H
#define CHESS_GRIDELEMENT_H

#include <SFML/Graphics.hpp>

class GridElement {

public:
    GridElement();
    GridElement(int x, int y, int size, sf::Color color);
    sf::RectangleShape rectangle;
private:
    int posX;
    int posY;
    int size;
    sf::Color color;
};


#endif //CHESS_GRIDELEMENT_H
