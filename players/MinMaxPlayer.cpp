//
// Created by Lukas Bos on 13/12/2017.
//

#include <iostream>
#include "MinMaxPlayer.h"


using namespace sf;

MinMaxPlayer::MinMaxPlayer() {}

MinMaxPlayer::MinMaxPlayer(PieceColor color) : Player(color) {}

String MinMaxPlayer::getType() {
    return type;
}

Move *MinMaxPlayer::getNextMove(Board *board) {
    RenderWindow &window = board->window;
    std::vector<ChessPiece *> pieces = board->getPiecesByColor(color);

    GridElement *bestElement = NULL;
    ChessPiece *pieceToMove = NULL;
    int highestScore = 0;

    // make a copy of the board to simulate a game
    Board fakeBoard = *board;

    // fakeBoard.doMove();

    for (int i = 0; i < pieces.size(); i++) {
        ChessPiece *piece = pieces[i];
        std::vector<GridElement *> moves = piece->getAvailableMoves(true);

        for (int j = 0; j < moves.size(); j++) {
            GridElement *element = moves[j];

            int elementScore = 0;
            if (element->chessPiece) {
                elementScore += element->chessPiece->pieceScore;
            }

            elementScore += piece->getLocationScore(element->coordinates.x, element->coordinates.y);

            if (elementScore >= highestScore) {
                highestScore = elementScore;
                bestElement = element;
                pieceToMove = piece;
            }
        }
    }
    return new Move(pieceToMove->location, bestElement); // return best move
}


