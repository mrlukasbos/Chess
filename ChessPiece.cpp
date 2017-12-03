//
// Created by Lukas Bos on 30/11/2017.
//

#include <iostream>
#include "ChessPiece.h"

ChessPiece::ChessPiece(PieceType type, PieceColor color, GridElement *location) : type(type), color(color),
                                                                                  location(location) {

    std::string names[] = {"King", "Queen", "Rook", "Bishop", "Knight", "Pawn"};


    if (color == BLACK) {
        imageUrlPrefix = "Black";
    } else {
        imageUrlPrefix = "White";
    }

    img.loadFromFile("images/" + imageUrlPrefix + names[type] + ".png");
}

void ChessPiece::drawChessPiece(sf::RenderWindow &window) {

    //It's an example, you have to keep the sf::Texture and sf::Sprite as members of your class
    texture.loadFromImage(img);
    sprite.setTexture(texture, true);
    sprite.setPosition(sf::Vector2f(location->posX + 10, location->posY + 10)); // absolute position
    window.draw(sprite);

}
