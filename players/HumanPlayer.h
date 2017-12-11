//
// Created by Lukas Bos on 11/12/2017.
//

#ifndef CHESS_HUMANPLAYER_H
#define CHESS_HUMANPLAYER_H


#include "../constants.h"
#include "../Board.h"
#include "../Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer();
    HumanPlayer(PieceColor color);
    Move *getNextMove(Board *board);

    sf::String getType();
private:
    Move *DetermineMoveFromMousePos(Board *board, int x, int y);

    sf::String type = "HumanPlayer";
};


#endif //CHESS_HUMANPLAYER_H
