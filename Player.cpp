//
// Created by Lukas Bos on 11/12/2017.
//

#include "Player.h"

Player::Player() = default;

Player::Player(PieceColor color) : color(color) {}

String Player::getType() {
  return type;
}

void Player::setNextMove(Move *move) {
  this->nextMove = move;
}
const PieceColor Player::getColor() const {
  return color;
}
void Player::setColor(PieceColor color) {
  this->color = color;
}
