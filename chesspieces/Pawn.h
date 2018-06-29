//
// Created by Lukas Bos on 04/12/2017.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "../ChessPiece.h"

using namespace std;

class Pawn : public ChessPiece {
public:
    Pawn(Board *, Square *, PieceColor );
    vector<Square *> getAvailableSquares(bool) override;
    vector<Move *> getAvailableMoves(bool) override;
    vector<Move *> addEnPassantMoves(vector<Move *>);
};

#endif //CHESS_PAWN_H
