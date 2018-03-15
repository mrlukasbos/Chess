//
// Created by Lukas Bos on 11/12/2017.
//

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include "Square.h"
#include "ChessPiece.h"

class Square;

class ChessPiece;
class Move {
public:
    Move();
    Move(Square *startOfMove, Square *endOfMove);
    Move(Square *startOfMove, Square *endOfMove, bool isSimulated);

    Square *startOfMove;
    Square *endOfMove;

    ChessPiece *initialPiece;
    ChessPiece *takenPiece;

    bool isSimulated = false;

    std::string name;
    std::string getName();

private:
    void identifyPieces();
};


#endif //CHESS_MOVE_H
