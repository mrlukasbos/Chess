//
// Created by Lukas Bos on 11/12/2017.
//

#ifndef CHESS_HUMANPLAYER_H
#define CHESS_HUMANPLAYER_H


#include "../constants.h"
#include "../Board.h"
#include "../Player.h"
#include "../PieceColor.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(PieceColor color);
    Move * getNextMove(Board *board);
private:
    Move *DetermineMoveFromMousePos(Board * board, int x, int y);
};


#endif //CHESS_HUMANPLAYER_H
