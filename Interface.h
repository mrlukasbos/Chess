//
// Created by Lukas Bos on 19/02/2018.
//

#ifndef CHESS_INTERFACE_H
#define CHESS_INTERFACE_H

#include <SFML/Graphics.hpp>
#include "Board.h"

using namespace sf;

class Board;

class Interface {
private:
    Font font;
    Font boldFont;
    Board * board;
    void drawBoard();
    void drawChessPiece(ChessPiece *, Vector2f);
    bool SquareIsAvailableMoveOfSelectedSquare(Square *);
    Square * selectedSquare = nullptr;
    RenderWindow &window;

    const Color darkSquareColor = Color(100, 100, 150);
    const Color lightSquareColor = Color(255, 255, 255);
    const Color menuColor = Color(200, 200, 200);
    const Color boardBackgroundColor = Color(0, 0, 0);
    const Color coordinateLettersColor = Color(255, 255, 255);

 public:
    Interface(Board *, RenderWindow &);
    void handleEvent(Event event);
    Move * getHumanMove();
    void draw();
};


#endif //CHESS_INTERFACE_H
