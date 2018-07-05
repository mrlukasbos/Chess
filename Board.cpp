/*
 * Board.cpp
 * Created by Lukas Bos on 30/11/2017.
 * Board is where the game is played.
 * Contains: Check, Checkmate, initial positions and allows moves to be set on the board.
*/

#include <iostream>
#include "Board.h"
#include "chesspieces/Rook.h"
#include "chesspieces/Bishop.h"
#include "chesspieces/Knight.h"
#include "chesspieces/Pawn.h"
#include "chesspieces/Queen.h"
#include "chesspieces/King.h"

using namespace sf;

Board::Board() {
  // create the squares of the board
  for (short i = 0; i < 8; i++) {
    for (short j = 0; j < 8; j++) {
      Vector2i coordinates = Vector2i(i, j);
      squares[i][j] = new Square(coordinates);
    }
  }
}

// set all pieces to the initial position
void Board::startGame(Player *bottomPlayer, Player *topPlayer, Player *currentPlayer) {
  this->bottomPlayer = bottomPlayer;
  this->topPlayer = topPlayer;
  this->currentPlayer = currentPlayer;
  initPieces();
}

void Board::initPieces() {
  clear();

  short kingXPosition = 3, queenXPosition = 4;
  if (topPlayer->getColor()==PieceColor::BLACK) {
    kingXPosition = 4;
    queenXPosition = 3;
  }

  // make all pieces twice
  for (int i = 0; i < 2; i++) {
    PieceColor color = topPlayer->getColor();
    short row = 0;

    if (i==1) {
      color = bottomPlayer->getColor();
      row = 7;
    }

    squares[0][row]->setChessPiece(new Rook(this, squares[0][row], color));
    squares[1][row]->setChessPiece(new Knight(this, squares[1][row], color));
    squares[2][row]->setChessPiece(new Bishop(this, squares[2][row], color));
    squares[queenXPosition][row]->setChessPiece(new Queen(this, squares[queenXPosition][row], color));
    squares[kingXPosition][row]->setChessPiece(new King(this, squares[kingXPosition][row], color));
    squares[5][row]->setChessPiece(new Bishop(this, squares[5][row], color));
    squares[6][row]->setChessPiece(new Knight(this, squares[6][row], color));
    squares[7][row]->setChessPiece(new Rook(this, squares[7][row], color));
  }

  // add pawns
  for (int i = 0; i < 8; i++) {
    squares[i][1]->setChessPiece(new Pawn(this, squares[i][1], topPlayer->getColor()));
    squares[i][6]->setChessPiece(new Pawn(this, squares[i][6], bottomPlayer->getColor()));
  }

}

void Board::doMove(Move *nextMove) {

  if (nextMove->getEnPassantTakenPiece()) {
    nextMove->getEnPassantTakenPiece()->getLocation()->removeChessPiece();
  }

  // move the chesspiece
  nextMove->getEndOfMove()->setChessPiece(nextMove->getStartOfMove()->getChessPiece());
  nextMove->getEndOfMove()->getChessPiece()->setLocation(nextMove->getEndOfMove());
  nextMove->getStartOfMove()->removeChessPiece();

  nextMove->getEndOfMove()->getChessPiece()->increaseAmountOfSteps(1);

  if (nextMove->isPromoting()) {

    nextMove->getEndOfMove()->removeChessPiece();

    if (currentPlayer->isHuman) {
      while (nextMove->getEndOfMove()->getChessPiece()==nullptr) {

        std::cout << "make a choice: q -> queen, r -> rook, b -> bishop, n -> knight" << std::endl;
        char PromotionChoice = (char) std::cin.get();

        Square *location = nextMove->getEndOfMove();
        PieceColor color = nextMove->getInitialPiece()->getColor();

        switch (PromotionChoice) {
          case 'q':nextMove->getEndOfMove()->setChessPiece(new Queen(this, location, color));
            break;
          case 'r':nextMove->getEndOfMove()->setChessPiece(new Rook(this, location, color));
            break;
          case 'b':nextMove->getEndOfMove()->setChessPiece(new Bishop(this, location, color));
            break;
          case 'n':nextMove->getEndOfMove()->setChessPiece(new Knight(this, location, color));
            break;
          default:
            std::cout << "error in input. make a choice: q -> queen, r -> rook, b -> bishop, n -> knight"
                      << std::endl;
        }
      }
    } else {
      nextMove->getEndOfMove()->setChessPiece(new Queen(this,
                                                        nextMove->getEndOfMove(),
                                                        nextMove->getInitialPiece()->getColor()));
    }
  }

  // if there is a castlingRook we must move it also
  if (nextMove->getCastlingRook()) {
    nextMove->getRookTargetSquare()->setChessPiece(nextMove->getCastlingRook());
    nextMove->getCastlingRook()->setLocation(nextMove->getRookTargetSquare());
    nextMove->getInitalRookSquare()->removeChessPiece();
  }

  if (!nextMove->isSimulated()) {
    cout << nextMove->getName() << endl;
  }

  allMoves.push_back(nextMove);
}

void Board::undoMove() {
  Move *move = allMoves.back();

  if (move) {
    allMoves.pop_back();
    // revive a piece when it was taken
    if (move->getTakenPiece()) {
      move->getTakenPiece()->setLocation(move->getEndOfMove());
    }
    move->getEndOfMove()->setChessPiece(move->getTakenPiece());

    move->getInitialPiece()->setLocation(move->getStartOfMove());
    move->getStartOfMove()->setChessPiece(move->getInitialPiece());
    move->getInitialPiece()->decreaseAmountOfSteps(1);

    // if there is a castlingRook we must move undo it also
    if (move->getCastlingRook()) {
      // move rook
      move->getInitalRookSquare()->setChessPiece(move->getCastlingRook());
      move->getCastlingRook()->setLocation(move->getInitalRookSquare());

      move->getRookTargetSquare()->removeChessPiece();
    }

    if (move->getEnPassantTakenPiece()) {
      move->getEnPassantTakenPiece()->getLocation()->setChessPiece(move->getEnPassantTakenPiece());
    }

    if (!move->isSimulated()) {
      cout << "Undo: " << move->getName() << endl;
    }
  }
}

bool Board::isInCheck(PieceColor color) {
  PieceColor enemyColor = inverse(color);

  // check if the enemy has moves that set the king of the chosen color in check
  for (ChessPiece *piece : getPiecesByColor(enemyColor)) {

    //considerotherpieces: true, considerCheck FALSE! otherwise infinite loop.
    for (Square *square : piece->getAvailableSquares(false)) {
      ChessPiece *pieceToHit = square->getChessPiece();
      if (pieceToHit && pieceToHit->getType()==KING && pieceToHit->getColor()==color) {
        return true;
      }
    }
  }
  return false;
}

bool Board::checkMate() {
  PieceColor color;
  if (isInCheck(PieceColor::WHITE)) color = PieceColor::WHITE;
  else if (isInCheck(PieceColor::BLACK)) color = PieceColor::BLACK;
  else return false;

  // look for all pieces and look if they have available moves
  for (ChessPiece *piece : getPiecesByColor(color)) {
    if (piece->getAvailableSquares(true).size() > 0) {
      return false;
    }
  }
  return true;
}

std::vector<ChessPiece *> Board::getPiecesByColor(PieceColor color) {
  std::vector<ChessPiece *> pieces;
  for (Square *square : getSquares()) {
    if (square->getChessPiece() && square->getChessPiece()->getColor()==color) {
      pieces.push_back(square->getChessPiece());
    }
  }
  return pieces;
}

void Board::checkGameStatus() {
  if (isInCheck(PieceColor::WHITE) || isInCheck(PieceColor::BLACK)) {
    if (checkMate()) {
      std::string winnerName = isInCheck(PieceColor::WHITE) ? "black" : "white";
      std::cout << "The winner is " << winnerName << endl;

      std::cout << "Restart game? Press B to play with Black and press W to play with white" << endl;


      // just start the game again ;-) switch players
      bottomPlayer->setColor(inverse(bottomPlayer->getColor()));
      topPlayer->setColor(inverse(topPlayer->getColor()));
      startGame(bottomPlayer, topPlayer, currentPlayer);
    }
  }
}

Square *Board::getSquare(short x, short y) {
  return squares[x][y];
}

vector<Square *> Board::getSquares() {
  vector<Square *> allSquares;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      allSquares.push_back(squares[i][j]);
    }
  }
  return allSquares;
}

const vector<Move *> &Board::getAllMoves() const {
  return allMoves;
}

Player *Board::getBottomPlayer() const {
  return bottomPlayer;
}

void Board::setBottomPlayer(Player *bottomPlayer) {
  Board::bottomPlayer = bottomPlayer;
}

Player *Board::getTopPlayer() const {
  return topPlayer;
}

void Board::setTopPlayer(Player *topPlayer) {
  Board::topPlayer = topPlayer;
}

Player *Board::getCurrentPlayer() const {
  return currentPlayer;
}

void Board::setCurrentPlayer(Player *currentPlayer) {
  Board::currentPlayer = currentPlayer;
}
void Board::clear() {
  for (Square *square : getSquares()) {
    square->removeChessPiece();
  }
}
