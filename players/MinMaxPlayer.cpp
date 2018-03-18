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
        std::vector<Move *> moves = piece->getAvailableMoves(true);

        for (int j = 0; j < moves.size(); j++) {
            Move *move = moves[j];

            int squareScore = 0;
            if (move->takenPiece) {
                squareScore += move->takenPiece->pieceScore;
            }

            Square *destinationSquare = move->endOfMove;

            squareScore += piece->getLocationScore(destinationSquare->coordinates.x, destinationSquare->coordinates.y);

            if (squareScore >= highestScore) {
                highestScore = squareScore;
                bestElement = destinationSquare;
                pieceToMove = piece;
            }
        }
    }

    Move *epicMove = new Move(&board, pieceToMove->location, bestElement); // return best move
    return epicMove;
}


