//
// Created by Lukas Bos on 30/11/2017.
// This class provides a backbone for all chess pieces

#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include <SFML/Graphics.hpp>
#include <array>
#include "constants.h"
#include "Square.h"
#include "Board.h"
#include "PieceColor.h"

using namespace sf;
using namespace std;

class Square;
class Move;
class Board;
class ChessPiece {
 protected:
  std::vector<Square *> removeMovesLeadingToSelfCheck(vector<Square *> moves);

  std::vector<Square *> calculateMovesForDirections(
      Square *location,
      Vector2i directions[],
      Board *board,
      PieceColor color,
      short amountOfDirections,
      short maxAmountOfSteps,
      bool considerCheck
  );

  PieceType type;
  Board *board;
  Square *location;
  PieceColor color;
  int amountOfSteps = 0;
 public:

  /// Initialize a chesspiece
  explicit ChessPiece();

  /// Initialize a chessPiece
  explicit ChessPiece(Board *board, Square *location, PieceColor color);

  /// Returns available squares
  virtual vector<Square *> getAvailableSquares(bool considerCheck) =0;

  /// Returns available moves
  virtual vector<Move *> getAvailableMoves(bool considerCheck);

  // Getters and setters
  PieceType getType() const;
  Square *getLocation() const;
  void setLocation(Square *location);
  PieceColor getColor() const;
  int getAmountOfSteps() const;
  void increaseAmountOfSteps(int amount);
  void decreaseAmountOfSteps(int amount);
};

#endif //CHESS_CHESSPIECE_H
