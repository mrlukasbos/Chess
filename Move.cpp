//
// Created by Lukas Bos on 11/12/2017.
//

#include "Move.h"


Move::Move() = default;

Move::Move(Board * board, Square *startOfMove, Square *endOfMove) : board(board), startOfMove(startOfMove), endOfMove(endOfMove) {
    identifyPieces();
    generateName();
}

Move::Move(Board * board, Square *startOfMove, Square *endOfMove, bool isSimulated) :  board(board), startOfMove(startOfMove), endOfMove(endOfMove), isSimulated(isSimulated) {
    identifyPieces();
    if (!isSimulated) generateName();
}

// Simulate move to look if this causes a check(mate).
void Move::generateName() {
    std::string shortNames[] = {"K", "Q", "R", "B", "N", ""};
    name = shortNames[initialPiece->type];
    if (takenPiece) name += 'x';
    name += endOfMove->name;

    bool tempIsSimulated = isSimulated;
    isSimulated = true;
    board->doMove(this);
    if (board->checkMate()) {
        name += '#';
    } else if (board->isInCheck(inverse(initialPiece->color))) {
        name += '+';
    }
    board->undoMove();
    isSimulated = tempIsSimulated;
}

void Move::identifyPieces() {
    initialPiece = startOfMove->chessPiece;
    takenPiece = endOfMove->chessPiece;
}