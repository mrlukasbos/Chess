//
// Created by Lukas Bos on 30/11/2017.
// This class provides a backbone for all chess pieces

#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include <SFML/Graphics.hpp>

class ChessPiece {
private:
    char letter = 'X';
    sf::Color color; //black or white
    sf::CircleShape circle;
public:
    ChessPiece();
    void drawChessPiece(sf::RenderWindow &window);
};


#endif //CHESS_CHESSPIECE_H
