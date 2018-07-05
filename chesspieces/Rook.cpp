// Created by Lukas Bos on 04/12/2017.

#include "Rook.h"

Rook::Rook(Board *board, Square *location, PieceColor color)
    : ChessPiece(board, location, color) {
  type = ROOK;
}

std::vector<Square *> Rook::getAvailableSquares(bool considerCheck) {
  Vector2i horizontalAndVerticalDirections[] = {
      Vector2i(0, 1),  // Down
      Vector2i(1, 0),  // Right
      Vector2i(0, -1), // Up
      Vector2i(-1, 0)  // Left
  };
  return calculateMovesForDirections(location, horizontalAndVerticalDirections, board, color, 4, 7, considerCheck);
}
