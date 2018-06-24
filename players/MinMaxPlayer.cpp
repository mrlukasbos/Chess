//
// Created by Lukas Bos on 13/12/2017.
//

#include <iostream>
#include "MinMaxPlayer.h"


using namespace sf;
using namespace std;

MinMaxPlayer::MinMaxPlayer() {
    type = "MinMaxPlayer";
    isHuman = false;
}

MinMaxPlayer::MinMaxPlayer(PieceColor color) : Player(color) {
    type = "MinMaxPlayer";
    isHuman = false;
}

Move *MinMaxPlayer::getNextMove(Board *board) {
    long highestScore = -999999;
    long newScore = -999999;
    Move * bestMove = nullptr;
    
    vector<ChessPiece *> pieces = board->getPiecesByColor(color);
    for (ChessPiece * piece : pieces) {
        vector<Move *> moves = piece->getAvailableMoves(true);
        for (Move * move : moves) {
            newScore = -getMoveScore(board, move, color, 0);
            
            if (newScore > highestScore) {
                highestScore = newScore;
                bestMove = move;
            }
        }
    }
    return bestMove;
}



long MinMaxPlayer::getMoveScore(Board *board, Move * move, PieceColor pieceColor, int exit) {
    if (exit >= exitMax) {
        move->isSimulated = true;
        board->doMove(move);
        long boardScore = getBoardScore(board, pieceColor);
        board->undoMove();
        return boardScore;
    }
    
    long highestScore, newScore;
    highestScore = INT_MIN;
    newScore = INT_MIN;

    move->isSimulated = true;
    board->doMove(move);

    vector<ChessPiece *> pieces = board->getPiecesByColor(inverse(pieceColor));
    for (ChessPiece * piece : pieces) {
        vector<Move *> moves = piece->getAvailableMoves(true);
        for (Move * move : moves) {
            newScore = -getMoveScore(board, move, inverse(pieceColor), ++exit);
            highestScore = max(newScore, highestScore);
        }
    }
    board->undoMove();
 
    return highestScore;
}

int MinMaxPlayer::getBoardScore(Board * board, PieceColor c) {
    
    if (board->isInCheck(inverse(c)) && board->checkMate()) {
        return INT_MIN;
    }
    
    if (board->isInCheck(c) && board->checkMate()) {
        return INT_MAX;
    }

    vector<ChessPiece *> friendlyPieces = board->getPiecesByColor(color);
    vector<ChessPiece *> opponentPieces = board->getPiecesByColor(inverse(color));

    return evaluateScore(friendlyPieces) - evaluateScore(opponentPieces);
}

int MinMaxPlayer::evaluateScore(vector<ChessPiece *> pieces) {
    
    int materialScore = 0;
    int locationScore = 0;
    int movementScore = 0;
    
    for (ChessPiece * piece : pieces) {
        materialScore += piece->pieceScore;
        locationScore += piece->getLocationScore(piece->location->coordinates.x, piece->location->coordinates.y);
        movementScore += piece->getAvailableSquares(false).size();
    }
    
    return materialScore + locationScore/20 + movementScore/20;
}



