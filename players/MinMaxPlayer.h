//
// Created by Lukas Bos on 13/12/2017.
//

#ifndef CHESS_MINMAXPLAYER_H
#define CHESS_MINMAXPLAYER_H

#include "../constants.h"
#include "../Board.h"
#include "../Player.h"
#include "../PieceColor.h"

using namespace std;

class MinMaxPlayer : public Player {
public:
    MinMaxPlayer();

    MinMaxPlayer(PieceColor color);

    Move * getNextMove(Board *board);
    
    long getMoveScore(Board *, Move *, PieceColor, int, long, long);
    
    Move * determineMove(Board*, PieceColor);
private:
    int exitMax = 8;
    int getBoardScore(Board *, PieceColor);
    int evaluateScore(vector<ChessPiece *>);
};

#endif //CHESS_MINMAXPLAYER_H
