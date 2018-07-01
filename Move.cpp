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

Move::Move(Board * board, Square *startOfMove, Square *endOfMove, bool isSimulated, CastlingSide castlingSide, ChessPiece * castlingRook, Square * rookTargetSquare, Square * initalRookSquare):  board(board), startOfMove(startOfMove), endOfMove(endOfMove), isSimulated(isSimulated), castlingSide(castlingSide), castlingRook(castlingRook), rookTargetSquare(rookTargetSquare), initalRookSquare(initalRookSquare) {
    identifyPieces();
    if (!isSimulated) generateName();
}

// Simulate move to look if this causes a check(mate).
void Move::generateName() {
    if (castlingRook) {
        name = castlingSide == CastlingSide::QUEENSIDE ? "0-0-0" : "0-0";
        return;
    }
    char shortNames[] = "KQRBNP";
    name = shortNames[initialPiece->type];
    if (name == "P") name = ""; // pawn is usually not written down.
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
