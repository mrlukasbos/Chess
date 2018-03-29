// Created by Lukas Bos on 11/12/2017.

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "Square.h"
#include "CastlingSide.h"
#include "ChessPiece.h"

class Board;
class Square;
class ChessPiece;
class Move {
private:
    Board *board;
    void identifyPieces();
public:
    Move();
    Move(Board * board, Square *startOfMove, Square *endOfMove);
    Move(Board * board, Square *startOfMove, Square *endOfMove, bool isSimulated);

    Square *startOfMove;
    Square *endOfMove;

    ChessPiece *initialPiece;
    ChessPiece *takenPiece;

    bool isSimulated = false;

    std::string name;
    void generateName();
    CastlingSide getCastleSide();
    ChessPiece * castlingKing = nullptr;
    ChessPiece * castlingRook = nullptr;
};


#endif //CHESS_MOVE_H
