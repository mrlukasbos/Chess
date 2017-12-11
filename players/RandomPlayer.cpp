//
// Created by Lukas Bos on 11/12/2017.
//

#include "RandomPlayer.h"

using namespace sf;

RandomPlayer::RandomPlayer() {}

RandomPlayer::RandomPlayer(PieceColor color) : Player(color) {}

Move *RandomPlayer::getNextMove(Board *board) {
    RenderWindow &window = board->window;

    // for all elements
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            GridElement *element = board->elements[i][j];


            if (element->chessPiece && element->chessPiece->color == this->color) {
                if (!element->chessPiece->getAvailableMoves(true).empty()) { // if the chesspiece has available moves
                    return new Move(element, element->chessPiece->getAvailableMoves(true).at(0));
                }
            }
        }
    }

    return NULL;
}
