//
// Created by Lukas Bos on 30/11/2017.
//

#include "ChessPiece.h"

ChessPiece::ChessPiece() {

}

void ChessPiece::drawChessPiece(sf::RenderWindow &window) {
    circle.setPosition(10, 10);
    circle.setRadius(30);
    circle.setFillColor(sf::Color::Green);

    window.draw(circle);
}
