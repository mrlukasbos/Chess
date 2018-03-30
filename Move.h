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
    Move(Board * board, Square *startOfMove, Square *endOfMove, bool isSimulated, CastlingSide castlingSide, ChessPiece * castlingRook, Square * initalRookSquare, Square * rookTargetSquare);
    Square *startOfMove;
    Square *endOfMove;

    ChessPiece *initialPiece;
    ChessPiece *takenPiece;

    bool isSimulated = false;

    std::string name;
    void generateName();
    
    // castling variables
    CastlingSide castlingSide;
    ChessPiece * castlingRook = nullptr;
    Square * rookTargetSquare = nullptr;
    Square * initalRookSquare = nullptr;
    
    // pawn promotion variables
    bool isPromoting = false;
    ChessPiece * promotedPiece = nullptr;
};


#endif //CHESS_MOVE_H
