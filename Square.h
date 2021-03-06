// Created by Lukas Bos on 30/11/2017.

#ifndef CHESS_Square_H
#define CHESS_Square_H

#include <SFML/Graphics.hpp>
#include "ChessPiece.h"
#include "constants.h"

using namespace sf;
using namespace std;

class ChessPiece;
class Square {
 public:
  Square(Vector2i coordinates);
  string getName();
  ChessPiece *getChessPiece();
  Vector2i getCoordinates();
  void setChessPiece(ChessPiece *piece);
  void removeChessPiece();
 private:
  Vector2i coordinates;
  string name;
  ChessPiece *chessPiece = nullptr;
};

#endif //CHESS_Square_H
