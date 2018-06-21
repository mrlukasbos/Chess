// Created by Lukas Bos on 11/12/2017.

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "Square.h"
#include "CastlingSide.h"
#include "ChessPiece.h"

class Board;
class Square;
class Player;
class ChessPiece;
class Move {
private:
    Board *board;
    void identifyPieces();
public:
    Move();
    Move(Board *, Square *, Square *);
    Move(Board *, Square *, Square *, bool);
    Move(Board *, Square *, Square *, bool, CastlingSide, ChessPiece *, Square *, Square *);


    Square *startOfMove;
    Square *endOfMove;

    ChessPiece *initialPiece;
    ChessPiece *takenPiece;

    Player * player;

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

    // en passant variable
    ChessPiece * enPassantTakenPiece = nullptr;

};


#endif //CHESS_MOVE_H
