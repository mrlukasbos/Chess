//
// Created by Lukas Bos on 30/11/2017.
// This class provides a backbone for all chess pieces

#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include <SFML/Graphics.hpp>
#include "color.h"
#include "gridElement.h"

using namespace sf;

class GridElement;
class ChessPiece {
public:
    ChessPiece();

    ChessPiece(PieceColor color, GridElement *location);
    void drawChessPiece(sf::RenderWindow &window);

    PieceColor color;
    GridElement *location;
    std::string imageUrlPrefix;

    // image utils
    sf::Image img;
    sf::Texture texture;
    sf::Sprite sprite;
};


#endif //CHESS_CHESSPIECE_H
