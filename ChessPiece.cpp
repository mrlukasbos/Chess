//
// Created by Lukas Bos on 30/11/2017.
//

#include "ChessPiece.h"

ChessPiece::ChessPiece() {

}

void ChessPiece::drawChessPiece(sf::RenderWindow &window) {

    sf::Font font;
    font.loadFromFile("OpenSans-Bold.ttf");
    sf::Text text("R", font, 6);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(32);
    text.setPosition(40, 30);

    circle.setPosition(20, 20);
    circle.setRadius(30);
    circle.setFillColor(sf::Color::Green);

    window.draw(circle);
    window.draw(text);
}
