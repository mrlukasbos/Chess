//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_Square_H
#define CHESS_Square_H

#include <SFML/Graphics.hpp>
#include "ChessPiece.h"
#include "constants.h"

class ChessPiece;
class Square {

public:
    Square();

    Square(int x, int y, int size, sf::Color color, sf::Vector2i coordinates);
    sf::RectangleShape rectangle;
    void drawSquare(sf::RenderWindow &window);
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


#endif //CHESS_Square_H
