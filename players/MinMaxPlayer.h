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
  explicit MinMaxPlayer(PieceColor color, int depth);

  Move *getNextMove(Board *board) override;

  int getMoveScore(Board *, Move *, int, int, int);
 private:
  int depth;
  int getBoardScore(Board *, PieceColor);
  int evaluateScore(Board *, vector<ChessPiece *>);

  enum GamePhase {
    OPENING, MIDDLEGAME, ENDGAME
  };

  GamePhase phase = OPENING;
  int getLocationScore(Board *board, ChessPiece *piece, Vector2i location);
  int getPieceScore(ChessPiece *piece);
};

#endif //CHESS_MINMAXPLAYER_H
