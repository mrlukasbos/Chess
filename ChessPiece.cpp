//
// Created by Lukas Bos on 30/11/2017.
//

#include "ChessPiece.h"

ChessPiece::ChessPiece(PieceColor color) : color(color) {
    if (color == BLACK) {
        imageUrlPrefix = "Black";
    } else {
        imageUrlPrefix = "White";
    }
}

void ChessPiece::drawChessPiece(sf::RenderWindow &window) {

    //It's an example, you have to keep the sf::Texture and sf::Sprite as members of your class
    texture.loadFromImage(img);
    sprite.setTexture(texture, true);
    sprite.setPosition(sf::Vector2f(10, 10)); // absolute position
    window.draw(sprite);

}
