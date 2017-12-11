//
// Created by Lukas Bos on 11/12/2017.
//

#ifndef CHESS_RANDOMPLAYER_H
#define CHESS_RANDOMPLAYER_H

#include "../constants.h"
#include "../Board.h"
#include "../Player.h"

class RandomPlayer : public Player {
public:
    RandomPlayer();

    RandomPlayer(PieceColor color);

    Move *getNextMove(Board *board);

    sf::String getType();
private:
    sf::String type = "RandomPlayer";
};


#endif //CHESS_RANDOMPLAYER_H
