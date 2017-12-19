//
// Created by Lukas Bos on 11/12/2017.
//

#include "HumanPlayer.h"

using namespace sf;

HumanPlayer::HumanPlayer(sf::RenderWindow &window) : window(window) {
    type = "HumanPlayer";
}

HumanPlayer::HumanPlayer(PieceColor color, sf::RenderWindow &window) : Player(color), window(window) {
    type = "HumanPlayer";
}

Move *HumanPlayer::getNextMove(Board &board) {
    if (Mouse::isButtonPressed(Mouse::Left)) {
        return DetermineMoveFromMousePos(board, Mouse::getPosition(window).x, Mouse::getPosition(window).y);
    }

    return NULL;
}

Move *HumanPlayer::DetermineMoveFromMousePos(Board &board, int x, int y) {

    // for all elements
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            GridElement *element = board.elements[i][j];
            element->setSelected(false); // there should be no other elements be selected.

            bool elementIsClicked = x > element->posX && x < element->posX + BLOCK_SIZE
                                    && y > element->posY && y < element->posY + BLOCK_SIZE;

            if (elementIsClicked) {
                if (element->isFocused) {
                    return new Move(board.selectedGridElement, element);
                } else if (element->chessPiece && element->chessPiece->color == this->color) {
                    element->setSelected(true);
                    board.selectedGridElement = element;
                }
            }
        }
    }

    board.focusGridElements();
    return NULL;
}
