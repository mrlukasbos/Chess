//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "Square.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "PieceColor.h"

using namespace sf;
using namespace std;

class Player;
class Square;

class ChessPiece;
class Move;
class Board {
 private:
  void initPieces();

  void clear();

  /// The player at the bottom of the board
  Player *bottomPlayer;

  /// The player at the top of the board
  Player *topPlayer;

  /// The player which is to move next
  Player *currentPlayer;

  /// All squares on the board
  Square *squares[8][8];

  /// The vector of all moves that were done.
  vector<Move *> allMoves;

 public:
  /// Initializes a board
  Board();

  /// Constructs a board from an existing board (copies the board)
  Board(Board const &) = default;

  /// Starts a game on the board
  void startGame(Player *bottomPlayer, Player *topPlayer, Player *currentPlayer);

  /// Do a move on the board
  void doMove(Move *nextMove);

  /// Undo the last move on the board
  void undoMove();

  /// Checks if a color is in check and if there is checkmate
  void checkGameStatus();

  /// Return a vector of chesspieces by color
  vector<ChessPiece *> getPiecesByColor(PieceColor color);

  /// checks if the given color is in check on the board.
  bool isInCheck(PieceColor color);

  /// checks if there is a checkmate on the board. Use isInCheck() to view which color is checkmated.
  bool checkMate();

  /// return a vector of all squares
  vector<Square *> getSquares();

  /// return a specific square of the board
  Square *getSquare(short, short);

  /// return a vector of all previous moves
  const vector<Move *> &getAllMoves() const;

  // getters and setters
  void setCurrentPlayer(Player *currentPlayer);
  Player *getBottomPlayer() const;
  void setBottomPlayer(Player *bottomPlayer);
  Player *getTopPlayer() const;
  void setTopPlayer(Player *topPlayer);
  Player *getCurrentPlayer() const;
  void setAllMoves(const vector<Move *> &allMoves);
};

#endif //CHESS_BOARD_H
