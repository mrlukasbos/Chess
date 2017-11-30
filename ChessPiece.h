//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include <SFML/Graphics.hpp>

class ChessPiece {
private:
    sf::CircleShape circle;
public:
    ChessPiece();
    void drawChessPiece(sf::RenderWindow &window);
};


#endif //CHESS_CHESSPIECE_H
