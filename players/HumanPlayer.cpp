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

    // for all squares
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            Square *square = board.squares[i][j];
            square->setSelected(false); // there should be no other squares be selected.

            bool squareIsClicked = x > square->posX && x < square->posX + BLOCK_SIZE
                                    && y > square->posY && y < square->posY + BLOCK_SIZE;

            if (squareIsClicked) {
                if (square->isFocused) {
                    return new Move(board.selectedSquare, square);
                } else if (square->chessPiece && square->chessPiece->color == this->color) {
                    square->setSelected(true);
                    board.selectedSquare = square;
                }
            }
        }
    }

    board.focusSquares();
    return NULL;
}
