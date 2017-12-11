//
// Created by Lukas Bos on 11/12/2017.
//

#include "RandomPlayer.h"

using namespace sf;

RandomPlayer::RandomPlayer() {}

RandomPlayer::RandomPlayer(PieceColor color) : Player(color) {}

Move *RandomPlayer::getNextMove(Board *board) {
    RenderWindow &window = board->window;
    std::vector<ChessPiece *> pieces = board->getPiecesByColor(color);

    for (int i = 0; i < pieces.size(); i++) {
        ChessPiece *randomPiece = pieces[std::rand() % pieces.size()];
        std::vector<GridElement *> moves = randomPiece->getAvailableMoves(true);

        if (!moves.empty()) { // if the chesspiece has available moves
            return new Move(randomPiece->location, moves.at(std::rand() % moves.size())); // return random move
        }
    }

    return NULL;
}


String RandomPlayer::getType() {
    return type;
}