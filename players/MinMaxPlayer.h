//
// Created by Lukas Bos on 13/12/2017.
//

#ifndef CHESS_MINMAXPLAYER_H
#define CHESS_MINMAXPLAYER_H

#include "../constants.h"
#include "../Board.h"
#include "../Player.h"

class MinMaxPlayer : public Player {
public:
    MinMaxPlayer();

    MinMaxPlayer(PieceColor color);

    Move *getNextMove(Board &board);

};

#endif //CHESS_MINMAXPLAYER_H
