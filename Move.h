//
// Created by Lukas Bos on 11/12/2017.
//

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include "gridElement.h"

class Move {
public:
    Move();

    Move(GridElement *startOfMove, GridElement *endOfMove);

    GridElement *startOfMove;
    GridElement *endOfMove;

    Move *getReverseMove();
};


#endif //CHESS_MOVE_H
