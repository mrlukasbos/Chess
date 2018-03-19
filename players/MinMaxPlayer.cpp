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
        std::vector<Square *> moves = piece->getAvailableMoves(true);

        for (int j = 0; j < moves.size(); j++) {
            Square *square = moves[j];

            int squareScore = 0;
            if (square->chessPiece) {
                squareScore += square->chessPiece->pieceScore;
            }

            squareScore += piece->getLocationScore(square->coordinates.x, square->coordinates.y);

            if (squareScore >= highestScore) {
                highestScore = squareScore;
                bestElement = square;
                pieceToMove = piece;
            }
        }
    }

    Move *epicMove = new Move(&board, pieceToMove->location, bestElement); // return best move
    return epicMove;
}


