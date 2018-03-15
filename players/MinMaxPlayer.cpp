//
// Created by Lukas Bos on 13/12/2017.
//

#include <iostream>
#include "MinMaxPlayer.h"


using namespace sf;

MinMaxPlayer::MinMaxPlayer() {
    type = "MinMaxPlayer";
}

MinMaxPlayer::MinMaxPlayer(PieceColor color) : Player(color) {
    type = "MinMaxPlayer";
}

Move *MinMaxPlayer::getNextMove(Board &board) {
    std::vector<ChessPiece *> pieces = board.getPiecesByColor(color);

    Square *bestElement = NULL;
    ChessPiece *pieceToMove = NULL;
    int highestScore = -999999;

    for (int i = 0; i < pieces.size(); i++) {
        ChessPiece *piece = pieces[i];
        std::vector<Square *> moves = piece->getAvailableMoves(true, true);

        for (int j = 0; j < moves.size(); j++) {
            Square *element = moves[j];

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


    // make a copy of the board to simulate a game
    Board fakeBoard = Board(board);

    Move *epicMove = new Move(pieceToMove->location, bestElement); // return best move

    //  fakeBoard.doMove(epicMove);

    return epicMove;
}


