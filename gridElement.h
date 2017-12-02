//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_GRIDELEMENT_H
#define CHESS_GRIDELEMENT_H

#include <SFML/Graphics.hpp>
#include "ChessPiece.h"

#include "color.h"

class ChessPiece;
class GridElement {

public:
    GridElement();
    GridElement(int x, int y, int size, sf::Color color, std::string name);
    sf::RectangleShape rectangle;
    void drawGridElement(sf::RenderWindow &window);
    int posX;
    int posY;
    bool isSelected = false;
    void setSelected(bool selected);
    sf::Color color;
    std::string name;
    int size;

    ChessPiece *chessPiece = NULL;

    void setChessPiece(ChessPiece *piece);
};


#endif //CHESS_GRIDELEMENT_H
