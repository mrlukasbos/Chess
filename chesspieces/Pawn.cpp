//
// Created by Lukas Bos on 04/12/2017.
//

#include <iostream>
#include "Pawn.h"

Pawn::Pawn(Board *board, Square *location, PieceColor color)
    : ChessPiece(board, location, color) {
  type = PAWN;
}

vector<Move *> Pawn::getAvailableMoves(bool considerCheck) {
  std::vector<Move *> moves;
  moves.reserve(50);

  for (Square *square : getAvailableSquares(considerCheck)) {
    Move *move = new Move(board, location, square);
    // when a pawn reaches bottom or top it can promote
    if (square->getCoordinates().y==7 || square->getCoordinates().y==0) {
      move->setPromoting(true);
    }
    moves.push_back(move);
  }
  return addEnPassantMoves(moves);
}

vector<Square *> Pawn::getAvailableSquares(bool considerCheck) {
  std::vector<Square *> availableMoves;
  availableMoves.reserve(5); // a pawn has never more than 5 moves

  int y = location->getCoordinates().y;
  int x = location->getCoordinates().x;

  bool isBottomColor = board->getBottomPlayer()->getColor()==color;
  int direction = isBottomColor ? -1 : 1;

  Vector2i pawnDirections[] = {
      Vector2i(0, 1),
      Vector2i(0, 2),
  };

  Vector2i pawnCaptureDirections[]{
      Vector2i(1, 1),
      Vector2i(-1, 1),
  };

  // 2 directions
  for (int i = 0; i < 2; i++) {
    int xLocation = x + pawnCaptureDirections[i].x;
    int yLocation = y + (direction*pawnCaptureDirections[i].y); // reverse ydirection for other color

    bool squareExists = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;
    if (squareExists) {
      Square *square = board->getSquare(xLocation, yLocation);
      if (square->getChessPiece() && square->getChessPiece()->getColor()!=color) {
        availableMoves.push_back(square);
      }
    }
  }

  int maxAmountOfSteps = (amountOfSteps > 0) ? 1 : 2;

  for (int i = 0; i < maxAmountOfSteps; i++) {
    int yLocation = y + (direction*pawnDirections[i].y); // reverse ydirection for other color

    // no need to check for x; we do not change it
    bool squareExists = yLocation >= 0 && yLocation < 8;
    if (squareExists) {
      Square *square = board->getSquare(x, yLocation);
      if (square->getChessPiece()) {
        break;
      }
      availableMoves.push_back(square);
    }
  }

  if (considerCheck) {
    return removeMovesLeadingToSelfCheck(availableMoves);
  }
  return availableMoves;
}

vector<Move *> Pawn::addEnPassantMoves(vector<Move *> moves) {
  Move *previousMove = board->getAllMoves().back();

  if (board->getAllMoves().size() > 0 && previousMove && previousMove->getInitialPiece()->getType()==PieceType::PAWN) {
    ChessPiece *opponentPawn = previousMove->getInitialPiece();
    Vector2i loc = this->getLocation()->getCoordinates();
    Vector2i opLoc = opponentPawn->getLocation()->getCoordinates();
    if (loc.y==opLoc.y && (((loc.x + 1)==opLoc.x) || (loc.x - 1)==opLoc.x)) {
      bool movedTwoSquaresFromBottom = opLoc.y==3;
      bool movedTwoSquaresFromTop = opLoc.y==4;
      if (opponentPawn->getAmountOfSteps()==1) {
        if (movedTwoSquaresFromBottom) {
          Move *enPassantMove = new Move(board, this->getLocation(), board->getSquare(opLoc.x, 2));
          enPassantMove->setEnPassantTakenPiece(opponentPawn);
          moves.push_back(enPassantMove);
        } else if (movedTwoSquaresFromTop) {
          Move *enPassantMove = new Move(board, this->getLocation(), board->getSquare(opLoc.x, 5));
          enPassantMove->setEnPassantTakenPiece(opponentPawn);
          moves.push_back(enPassantMove);
        }
      }
    }
  }
  return moves;
}
