//
// Created by Lukas Bos on 11/12/2017.
//

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer() {}

HumanPlayer::HumanPlayer(PieceColor color) : Player(color) {}

Move *HumanPlayer::getNextMove(Board *board) {
    return new Move(board->elements[1][1], board->elements[2][2]);
}