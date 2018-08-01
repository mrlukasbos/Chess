//
// Created by Lukas Bos on 19/02/2018.
//

#include "Interface.h"

using namespace sf;

Interface::Interface(Board *board, RenderWindow &window) : board(board), window(window) {
  font.loadFromFile("fonts/OpenSans-Regular.ttf");
  boldFont.loadFromFile("fonts/OpenSans-Bold.ttf");
}

void Interface::draw() {
  window.clear(menuColor);
  drawBoard();
  drawRecentMoves();
  drawCoordinates();
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
        if (getMoveBelongingToSelectedSquare(board->getSquare(i, j))) {
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

void Interface::drawRecentMoves() {
  int height = 20;

  for (int i = 0; i < board->getAllMoves().size(); i++) {

    if (i%2==0) {
      Text squareName(to_string(i/2 + 1) + ".", font, 18);
      squareName.setFillColor(Color::Black);
      squareName.setCharacterSize(18);
      squareName.setPosition(GAME_SIZE + 10, height);
      window.draw(squareName);

    }

    Move *move = board->getAllMoves()[i];
    Text squareName(move->getName(), font, 18);
    squareName.setFillColor(Color::Black);
    squareName.setCharacterSize(18);

    if (i%2==0) {
      squareName.setPosition(GAME_SIZE + 50, height);
    } else {
      squareName.setPosition(GAME_SIZE + 110, height);
      height += 20;
    }

    window.draw(squareName);
  }
}

void Interface::drawCoordinates() {
  string letters = "ABCDEFGH";

  for (short i = 0; i < 8; i++) {
    Text coordinateNumberPart(std::to_string(8 - i), boldFont, 18);
    Text coordinateLetterPart(letters[i], boldFont, 18);

    coordinateLetterPart.setFillColor(Color::White);
    coordinateLetterPart.setCharacterSize(20);
    coordinateLetterPart.setPosition(BOARD_BORDER_THICKNESS + 40 + (i*BLOCK_SIZE), GAME_SIZE - 40);

    coordinateNumberPart.setFillColor(Color::White);
    coordinateNumberPart.setCharacterSize(20);
    coordinateNumberPart.setPosition(15, BOARD_BORDER_THICKNESS + 40 + (i*BLOCK_SIZE));

    window.draw(coordinateLetterPart);
    window.draw(coordinateNumberPart);
  }
}



//void Interface::drawMaterialScore() {
//  int materialscore = 0;
//  for (ChessPiece *piece : board->getPiecesByColor(board->getBottomPlayer()->getColor())) {
//    materialScore += getPieceScore(piece);
//    locationScore += getLocationScore(board, piece, piece->getLocation()->getCoordinates());
//    movementScore += piece->getAvailableSquares(false).size();
//  }
//}

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
      if (selectedSquare!=nullptr && getMoveBelongingToSelectedSquare(square)) { // and if target square
        return getMoveBelongingToSelectedSquare(square);
      } else {
        selectedSquare = square;
      }
    }
  }
  return nullptr;
}

Move *Interface::getMoveBelongingToSelectedSquare(Square *square) {
  if (selectedSquare->getChessPiece()) {
    for (Move *move : selectedSquare->getChessPiece()->getAvailableMoves(true)) {
      if (move->getEndOfMove()==square) {
        return move;
      }
    }
  }
  return nullptr;
}