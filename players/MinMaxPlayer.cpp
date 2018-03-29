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

Move *MinMaxPlayer::getNextMove(Board *board) {
    std::vector<ChessPiece *> pieces = board->getPiecesByColor(color);

    Move * bestMove = nullptr;
    int highestScore = -999999;

    for (int i = 0; i < pieces.size(); i++) {
        ChessPiece *piece = pieces[i];
        
        std::vector<Move *> moves = piece->getAvailableMoves(true);

        for (int j = 0; j < moves.size(); j++) {
            Square * targetSquare = moves[j]->endOfMove;

            int squareScore = 0;
            if (targetSquare->chessPiece) {
                squareScore += targetSquare->chessPiece->pieceScore;
            }

            squareScore += piece->getLocationScore(targetSquare->coordinates.x, targetSquare->coordinates.y);

            if (squareScore >= highestScore) {
                highestScore = squareScore;
                bestMove = moves[j];
            }
        }
    }

    return bestMove;
}


