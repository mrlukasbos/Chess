//
// Created by Lukas Bos on 11/12/2017.
//

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include "gridElement.h"
#include "ChessPiece.h"

class GridElement;

class ChessPiece;
class Move {
public:
    Move();

    Move(GridElement *startOfMove, GridElement *endOfMove);

    GridElement *startOfMove;
    GridElement *endOfMove;

    ChessPiece *initialPiece;
    ChessPiece *takenPiece;

    Move *getReverseMove();
};


#endif //CHESS_MOVE_H
