//
// Created by Lukas Bos on 11/12/2017.
//

#include "Move.h"


Move::Move() = default;

Move::Move(Square *startOfMove, Square *endOfMove) : startOfMove(startOfMove), endOfMove(endOfMove) {
    identifyPieces();
}

Move::Move(Square *startOfMove, Square *endOfMove, bool isSimulated) : startOfMove(startOfMove), endOfMove(endOfMove), isSimulated(isSimulated) {
    identifyPieces();
}

std::string Move::getName() {
    std::string shortNames[] = {"K", "Q", "R", "B", "N", ""};
    name = shortNames[initialPiece->type];
    if (takenPiece) name += 'x';
    name += endOfMove->name;

    // if checkmate name += '#';
    // else if (check) name += '+';

    return name;
}

void Move::identifyPieces() {
    initialPiece = startOfMove->chessPiece;
    takenPiece = endOfMove->chessPiece;
}