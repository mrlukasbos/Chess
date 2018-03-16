//
// Created by Lukas Bos on 11/12/2017.
//

#include "Player.h"

Player::Player() = default;

Player::Player(PieceColor color) : color(color) {}

Move *Player::getNextMove(Board &board) { return nullptr; }

String Player::getType() {
    return type;
}