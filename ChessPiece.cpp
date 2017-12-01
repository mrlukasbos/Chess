//
// Created by Lukas Bos on 30/11/2017.
//

#include "ChessPiece.h"

ChessPiece::ChessPiece() {

}

void ChessPiece::drawChessPiece(sf::RenderWindow &window) {

// Load an image file from a file
    sf::Image img;
    img.loadFromFile("images/whiteRook.png");

    //It's an example, you have to keep the sf::Texture and sf::Sprite as members of your class
    sf::Texture texture;
    texture.loadFromImage(img);
    sf::Sprite sprite;
    sprite.setTexture(texture, true);
    sprite.setPosition(sf::Vector2f(10, 10)); // absolute position


    // Load an image file from a file
    sf::Image img2;
    img2.loadFromFile("images/blackQueen.png");

    //It's an example, you have to keep the sf::Texture and sf::Sprite as members of your class
    sf::Texture texture2;
    texture2.loadFromImage(img2);
    sf::Sprite sprite2;
    sprite2.setTexture(texture2, true);
    sprite2.setPosition(sf::Vector2f(110, 10)); // absolute position


    window.draw(sprite);
    window.draw(sprite2);

}
