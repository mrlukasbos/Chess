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
    RenderWindow &window;
    Board &board;
public:
    Interface(RenderWindow &window, Board &board);
    void showCurrentPlayerText(Player *currentPlayer);
    void showSelectedSquareName();
    void showPlayerTypes();
    void showCoordinates();
    void showBoardBackground();
    };


#endif //CHESS_INTERFACE_H
