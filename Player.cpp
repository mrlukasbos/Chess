//
// Created by Lukas Bos on 11/12/2017.
//

#include "Player.h"

Player::Player() {}

Player::Player(PieceColor color) : color(color) {}

Move *Player::getNextMove(Board &board) {}

String Player::getType() {
    return type;
}