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
    Player *currentPlayer;
public:
    Interface(RenderWindow &window, Board &board);

    void showCurrentPlayerText(Player *currentPlayer);

    void showSelectedGridElementName();

    void showPlayerTypes();
};


#endif //CHESS_INTERFACE_H