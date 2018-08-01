//
// Created by Lukas Bos on 04/12/2017.
//

#include "Knight.h"

Knight::Knight(Board *board, Square *location, PieceColor color)
    : ChessPiece(board, location, color) {
  type = KNIGHT;
  name = "Knight";
  letter = 'N';
}

std::vector<Square *> Knight::getAvailableSquares(bool considerCheck) {
  Vector2i knightDirections[] = {
      Vector2i(-2, 1),
      Vector2i(-2, -1),
      Vector2i(-1, 2),
      Vector2i(-1, -2),
      Vector2i(1, 2),
      Vector2i(1, -2),
      Vector2i(2, 1),
      Vector2i(2, -1)
  };
  return calculateMovesForDirections(location, knightDirections, board, color, 8, 1, considerCheck);
}
