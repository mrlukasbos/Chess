// Created by Lukas Bos on 04/12/2017.

#include "Bishop.h"

Bishop::Bishop(Board *board, Square *location, PieceColor color)
    : ChessPiece(board, location, color) {
  type = BISHOP;
}

std::vector<Square *> Bishop::getAvailableSquares(bool considerCheck) {
  Vector2i diagonalDirections[] = {
      Vector2i(1, 1),   // Right-Down
      Vector2i(1, -1),  // Right-Up
      Vector2i(-1, -1), // Left-Up
      Vector2i(-1, 1)   // Left-Down
  };
  return calculateMovesForDirections(location, diagonalDirections, board, color, 4, 7, considerCheck);
}
