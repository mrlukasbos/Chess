//
// Created by Lukas Bos on 11/12/2017.
//

#include "RandomPlayer.h"

using namespace sf;

RandomPlayer::RandomPlayer() {
    type = "Randomplayer";
    isHuman = false;

}

RandomPlayer::RandomPlayer(PieceColor color) : Player(color) {
    type = "Randomplayer";
    isHuman = false;

}

Move *RandomPlayer::getNextMove(Board * board) {
    std::vector<ChessPiece *> pieces = board->getPiecesByColor(color);

    for (int i = 0; i < pieces.size(); i++) {
        ChessPiece *randomPiece = pieces[std::rand() % pieces.size()];
        std::vector<Move *> moves = randomPiece->getAvailableMoves(true);

        if (!moves.empty()) { // if the chesspiece has available moves
            return moves.at(std::rand() % moves.size()); // return random move
        }
    }

    return NULL;
}
