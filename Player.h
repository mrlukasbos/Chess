//
// Created by Lukas Bos on 11/12/2017.
//

#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Board.h"
#include "Move.h"

using namespace sf;

class Move;

class Board;
class Player {
public:
    Player();

    Player(PieceColor color);

    PieceColor color;

    virtual Move *getNextMove(Board *board);
};


#endif //CHESS_PLAYER_H
