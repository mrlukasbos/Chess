//
// Created by Lukas Bos on 11/12/2017.
//

#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <SFML/Graphics.hpp>
#include "PieceColor.h"
#include "Board.h"
#include "Move.h"

using namespace sf;

class Move;

class Board;
class Player {
public:
    Player();
    explicit Player(PieceColor color);
    PieceColor color;

    virtual Move *getNextMove(Board *board) =0;
    bool isHuman = false;
    sf::String getType();
    sf::String type;
};


#endif //CHESS_PLAYER_H
