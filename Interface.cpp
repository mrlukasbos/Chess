//
// Created by Lukas Bos on 19/02/2018.
//

#include "Interface.h"

using namespace sf;

Interface::Interface(Board *board, RenderWindow &window) : board(board), window(window) {
  font.loadFromFile("OpenSans-Regular.ttf");
  boldFont.loadFromFile("OpenSans-Bold.ttf");
}

void Interface::draw() {
  window.clear(menuColor);
  drawBoard();
}

void Interface::drawBoard() {
  RectangleShape boardBackground;
  boardBackground.setPosition(10, 10);
  boardBackground.setSize(Vector2f(GAME_SIZE - 20, GAME_SIZE - 20));
  boardBackground.setFillColor(boardBackgroundColor);
  window.draw(boardBackground);

  for (short i = 0; i < 8; i++) {
    for (short j = 0; j < 8; j++) {
      RectangleShape square;
      Color squareColor = darkSquareColor;
      if ((i + j)%2==0) {
        squareColor = lightSquareColor;
      }
      square.setFillColor(squareColor);

      int posX = BOARD_BORDER_THICKNESS + i*BLOCK_SIZE;
      int posY = BOARD_BORDER_THICKNESS + j*BLOCK_SIZE;
      Vector2f position = Vector2f(posX, posY);

      square.setPosition(position.x + SELECTION_LINE_THICKNESS, position.y + SELECTION_LINE_THICKNESS);
      square.setSize(Vector2f(BLOCK_SIZE - 2*SELECTION_LINE_THICKNESS, BLOCK_SIZE - 2*SELECTION_LINE_THICKNESS));
      square.setOutlineThickness(SELECTION_LINE_THICKNESS);

      // Focus elements
      if (selectedSquare && selectedSquare->getChessPiece()) {
        ChessPiece *piece = selectedSquare->getChessPiece();

        if (SquareIsAvailableMoveOfSelectedSquare(board->getSquare(i, j))) {
          if (board->getSquare(i, j)->getChessPiece()) {
            square.setOutlineColor(Color(255, 0, 0));
          } else {
            square.setOutlineColor(Color(0, 255, 0));
          }
        } else {
          square.setOutlineColor(squareColor);
        }
      } else {
        square.setOutlineColor(squareColor);
      }

      if (board->getSquare(i, j)==selectedSquare) {
        square.setOutlineColor(Color::Green);

      }

      window.draw(square);

      // draw chesspieces
      if (board->getSquare(i, j)->getChessPiece()) {
        ChessPiece *piece = board->getSquare(i, j)->getChessPiece();
        drawChessPiece(piece, position);
      }
    }
  }
}

void Interface::drawChessPiece(ChessPiece *piece, Vector2f position) {
  Image img;
  string names[] = {"King", "Queen", "Rook", "Bishop", "Knight", "Pawn"};
  string imageUrlPrefix = piece->getColor()==PieceColor::BLACK ? "Black" : "White";
  img.loadFromFile("images/" + imageUrlPrefix + names[piece->getType()] + ".png");

  Texture texture;
  Sprite sprite;

  texture.loadFromImage(img);
  texture.setSmooth(true);
  sprite.setScale(0.9, 0.9);
  sprite.setTexture(texture, true);
  sprite.setPosition(position.x + 10, position.y + 10); // absolute position
  window.draw(sprite);
}

Move *Interface::getHumanMove() {
  int mouseX = Mouse::getPosition(window).x;
  int mouseY = Mouse::getPosition(window).y;

  for (Square *square : board->getSquares()) {
    int squareLeftSide = square->getCoordinates().x*BLOCK_SIZE + BOARD_BORDER_THICKNESS;
    int squareRightSide = squareLeftSide + BLOCK_SIZE;
    int squareTopSide = square->getCoordinates().y*BLOCK_SIZE + BOARD_BORDER_THICKNESS;
    int squareBottomSide = squareTopSide + BLOCK_SIZE;

    if (squareLeftSide < mouseX
        && squareRightSide > mouseX
        && squareTopSide < mouseY
        && squareBottomSide > mouseY) {

      if (selectedSquare!=nullptr && SquareIsAvailableMoveOfSelectedSquare(square)) { // and if target square
        return new Move(board, selectedSquare, square);
      } else {
        selectedSquare = square;
      }
    }
  }
  return nullptr;
}

bool Interface::SquareIsAvailableMoveOfSelectedSquare(Square *square) {
  if (selectedSquare->getChessPiece()) {
    for (Move *move : selectedSquare->getChessPiece()->getAvailableMoves(true)) {
      if (move->getEndOfMove()==square) {
        return true;
      }
    }
  }
  return false;
}