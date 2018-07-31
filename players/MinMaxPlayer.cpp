//
// Created by Lukas Bos on 13/12/2017.
//

#include <iostream>
#include "MinMaxPlayer.h"

using namespace sf;
using namespace std;

MinMaxPlayer::MinMaxPlayer(PieceColor color)
    : Player(color) {
  type = "MinMaxPlayer";
  isHuman = false;
}

Move *MinMaxPlayer::getNextMove(Board *board) {
  long highestScore = INT_MIN;
  long newScore = INT_MIN;
  Move *bestMove = nullptr;

  vector<ChessPiece *> pieces = board->getPiecesByColor(color);
  for (ChessPiece *piece : pieces) {
    vector<Move *> moves = piece->getAvailableMoves(true);
    for (Move *move : moves) {
      newScore = getMoveScore(board, move, color, 0, INT_MIN, INT_MAX);
      if (newScore > highestScore) {
        highestScore = newScore;
        bestMove = move;
      }
    }
  }
  return bestMove;
}

long MinMaxPlayer::getMoveScore(Board *board, Move *move, PieceColor pieceColor, int exit, long alpha, long beta) {
  if (exit >= depth) {
    move->setSimulated(true);
    board->doMove(move);
    long boardScore = getBoardScore(board, pieceColor);
    board->undoMove();
    return boardScore;
  }

  long bestScore, newScore;

  // maximize
  if (pieceColor==color) {
    bestScore = INT_MAX;
    newScore = INT_MAX;

    move->setSimulated(true);
    board->doMove(move);

    vector<ChessPiece *> pieces = board->getPiecesByColor(inverse(color));
    for (ChessPiece *piece : pieces) {
      vector<Move *> moves = piece->getAvailableMoves(true);
      for (Move *move : moves) {
        newScore = -getMoveScore(board, move, inverse(color), ++exit, alpha, beta);
        bestScore = min(newScore, bestScore);
        alpha = min(alpha, bestScore);
        if (beta < alpha) break;
      }
      if (beta < alpha) break;
    }
    board->undoMove();
  } else { // Minimize
    bestScore = INT_MIN;
    newScore = INT_MIN;

    move->setSimulated(true);
    board->doMove(move);

    vector<ChessPiece *> pieces = board->getPiecesByColor(color);
    for (ChessPiece *piece : pieces) {
      vector<Move *> moves = piece->getAvailableMoves(true);
      for (Move *move : moves) {
        newScore = -getMoveScore(board, move, color, ++exit, alpha, beta);
        bestScore = max(newScore, bestScore);

        beta = max(beta, bestScore);
        if (beta < alpha) break;
      }
      if (beta < alpha) break;
    }
    board->undoMove();
  }
  return bestScore;
}

int MinMaxPlayer::getBoardScore(Board *board, PieceColor c) {
  vector<ChessPiece *> friendlyPieces = board->getPiecesByColor(c);
  vector<ChessPiece *> opponentPieces = board->getPiecesByColor(inverse(c));

  long score = evaluateScore(board, friendlyPieces) - evaluateScore(board, opponentPieces);
  return score;
}

int MinMaxPlayer::evaluateScore(Board *board, vector<ChessPiece *> pieces) {
  int materialScore = INT_MIN;
  int locationScore = INT_MIN;
  int movementScore = INT_MIN;

  for (ChessPiece *piece : pieces) {
    materialScore += getPieceScore(piece);
    locationScore += getLocationScore(board, piece, piece->getLocation()->getCoordinates());
    movementScore += piece->getAvailableSquares(false).size();
  }

  if (materialScore < 9900) phase = MIDDLEGAME;
  if (materialScore < 9000) phase = ENDGAME;

  int materialFactor = 1;
  double locationFactor = phase==OPENING ? 1 : .25;
  int movementFactor = phase==ENDGAME ? 2 : 1;

  long total = materialScore*materialFactor
      + locationScore*locationFactor
      + movementScore*movementFactor;
  return total;
}

int MinMaxPlayer::getLocationScore(Board *board, ChessPiece *piece, Vector2i location) {
  // source: https://chessprogramming.wikispaces.com/Simplified+evaluation+function

  PieceType type = piece->getType();
  array<array<int, 8>, 8> locationScores;

  switch (type) {
    case KING:
      locationScores = {{
                            {{-30, -40, -40, -50, -50, -40, -40, -30}},
                            {{-30, -40, -40, -50, -50, -40, -40, -30}},
                            {{-30, -40, -40, -50, -50, -40, -40, -30}},
                            {{-30, -40, -40, -50, -50, -40, -40, -30}},
                            {{-20, -30, -30, -40, -40, -30, -30, -20}},
                            {{-10, -20, -20, -20, -20, -20, -20, -10}},
                            {{20, 20, 0, 0, 0, 0, 20, 20}},
                            {{20, 30, 10, 0, 0, 10, 30, 20}}}};
      break;
    case QUEEN:
      locationScores = {{
                            {{-20, -10, -10, -5, -5, -10, -10, -20}},
                            {{-10, 0, 0, 0, 0, 0, 0, -10}},
                            {{-10, 0, 5, 5, 5, 5, 0, -10}},
                            {{-5, 0, 5, 5, 5, 5, 0, -5}},
                            {{0, 0, 5, 5, 5, 5, 0, -5}},
                            {{-10, 5, 5, 5, 5, 5, 0, -10}},
                            {{-10, 0, 5, 0, 0, 0, 0, -10}},
                            {{-20, -10, -10, -5, -5, -10, -10, -20}}
                        }};
      break;
    case ROOK:
      locationScores = {{
                            {{0, 0, 0, 0, 0, 0, 0, 0}},
                            {{5, 10, 10, 10, 10, 10, 10, 5}},
                            {{-5, 0, 0, 0, 0, 0, 0, -5}},
                            {{-5, 0, 0, 0, 0, 0, 0, -5}},
                            {{-5, 0, 0, 0, 0, 0, 0, -5}},
                            {{-5, 0, 0, 0, 0, 0, 0, -5}},
                            {{-5, 0, 0, 0, 0, 0, 0, -5}},
                            {{0, 0, 0, 5, 5, 0, 0, 0}}
                        }};
      break;
    case KNIGHT:
      locationScores = {{
                            {{-50, -40, -30, -30, -30, -30, -40, -50}},
                            {{-40, -20, 0, 0, 0, 0, -20, -40}},
                            {{-30, 0, 10, 15, 15, 10, 0, -30}},
                            {{-30, 5, 15, 20, 20, 15, 5, -30}},
                            {{-30, 0, 15, 20, 20, 15, 0, -30}},
                            {{-30, 5, 10, 15, 15, 10, 5, -30}},
                            {{-40, -20, 0, 5, 5, 0, -20, -40}},
                            {{-50, -40, -30, -30, -30, -30, -40, -50}}
                        }};
      break;
    case BISHOP:
      locationScores = {{
                            {{-20, -10, -10, -10, -10, -10, -10, -20}},
                            {{-10, 0, 0, 0, 0, 0, 0, -10}},
                            {{-10, 0, 5, 10, 10, 5, 0, -10}},
                            {{-10, 5, 5, 10, 10, 5, 5, -10}},
                            {{-10, 0, 10, 10, 10, 10, 0, -10}},
                            {{-10, 10, 10, 10, 10, 10, 10, -10}},
                            {{-10, 5, 0, 0, 0, 0, 5, -10}},
                            {{-20, -10, -10, -10, -10, -10, -10, -20}}
                        }};
      break;
    case PAWN:
      locationScores = {{
                            {{0, 0, 0, 0, 0, 0, 0, 0}},
                            {{50, 50, 50, 50, 50, 50, 50, 50}},
                            {{10, 10, 20, 30, 30, 20, 10, 10}},
                            {{5, 5, 10, 25, 25, 10, 5, 5}},
                            {{0, 0, 0, 20, 20, 0, 0, 0}},
                            {{5, -5, -10, 0, 0, -10, -5, 5}},
                            {{5, 10, 10, -20, -20, 10, 10, 5}},
                            {{0, 0, 0, 0, 0, 0, 0, 0}}
                        }};
  }

  int y = location.y;
  if (board->getBottomPlayer()->getColor()==piece->getColor()) {
    y = 7 - location.y;
  }

  return locationScores[y][location.x];
}
int MinMaxPlayer::getPieceScore(ChessPiece *piece) {
  switch (piece->getType()) {
    case KING: return 10000;
    case QUEEN: return 900;
    case ROOK: return 500;
    case BISHOP: return 330;
    case KNIGHT: return 320;
    case PAWN: return 100;
  }
  return 0;
}
