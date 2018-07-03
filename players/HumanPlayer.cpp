//
// Created by Lukas Bos on 11/12/2017.
//

#include "HumanPlayer.h"

using namespace sf;

HumanPlayer::HumanPlayer(PieceColor color) : Player(color) {
    type = "HumanPlayer";
    isHuman = true;
}

Move *HumanPlayer::getNextMove(Board *board) {
    return nullptr;
}


