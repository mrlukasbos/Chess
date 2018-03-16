//
// Created by Lukas Bos on 11/12/2017.
//

#include "Move.h"


Move::Move() = default;

Move::Move(Board * board, Square *startOfMove, Square *endOfMove) : board(board), startOfMove(startOfMove), endOfMove(endOfMove) {
    identifyPieces();
}

Move::Move(Board * board, Square *startOfMove, Square *endOfMove, bool isSimulated) :  board(board), startOfMove(startOfMove), endOfMove(endOfMove), isSimulated(isSimulated) {
    identifyPieces();
}

std::string Move::getName() {
    std::string shortNames[] = {"K", "Q", "R", "B", "N", ""};
    name = shortNames[initialPiece->type];
    if (takenPiece) name += 'x';
    name += endOfMove->name;
    if (board->isInCheck(inverse(initialPiece->color))) name += '+';
    return name;
}

void Move::identifyPieces() {
    initialPiece = startOfMove->chessPiece;
    takenPiece = endOfMove->chessPiece;
}