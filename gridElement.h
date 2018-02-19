//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_GRIDELEMENT_H
#define CHESS_GRIDELEMENT_H

#include <SFML/Graphics.hpp>
#include "ChessPiece.h"
#include "constants.h"

class ChessPiece;
class GridElement {

public:
    GridElement();

    GridElement(int x, int y, int size, sf::Color color, sf::Vector2i coordinates);
    sf::RectangleShape rectangle;
    void drawGridElement(sf::RenderWindow &window);
    int posX;
    int posY;
    bool isSelected = false;
    bool isFocused = false;
    bool isChecked = false;
    void setSelected(bool selected);

    void setFocused(bool focused);

    sf::Color color;
    sf::Vector2i coordinates;
    std::string name;
    int size;

    ChessPiece *chessPiece = NULL;

    void setChessPiece(ChessPiece *piece);
};


#endif //CHESS_GRIDELEMENT_H
