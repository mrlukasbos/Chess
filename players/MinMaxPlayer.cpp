//
// Created by Lukas Bos on 13/12/2017.
//

#include <iostream>
#include "MinMaxPlayer.h"


using namespace sf;
using namespace std;

MinMaxPlayer::MinMaxPlayer(PieceColor color) : Player(color) {
    type = "MinMaxPlayer";
    isHuman = false;
}

Move *MinMaxPlayer::getNextMove(Board *board) {
    long highestScore = INT_MIN;
    long newScore = INT_MIN;
    Move * bestMove = nullptr;
    
    vector<ChessPiece *> pieces = board->getPiecesByColor(color);
    for (ChessPiece * piece : pieces) {
        vector<Move *> moves = piece->getAvailableMoves(true);
        for (Move * move : moves) {
            newScore = getMoveScore(board, move, color, 0, INT_MIN, INT_MAX);
            
           // cout << move->name << "\t" << newScore << endl;
            
            if (newScore > highestScore) {
                highestScore = newScore;
                bestMove = move;
            }
        }
    }
    return bestMove;
}

long MinMaxPlayer::getMoveScore(Board *board, Move * move, PieceColor pieceColor, int exit, long alpha, long beta) {
    if (exit >= depth) {
        move->isSimulated = true;
        board->doMove(move);
        long boardScore = getBoardScore(board, pieceColor);
        board->undoMove();
        return boardScore;
    }
    
    long bestScore, newScore;

    // maximize
    if (pieceColor == color) {
        bestScore = INT_MAX;
        newScore = INT_MAX;
        
        move->isSimulated = true;
        board->doMove(move);
        
        vector<ChessPiece *> pieces = board->getPiecesByColor(inverse(color));
        for (ChessPiece * piece : pieces) {
            vector<Move *> moves = piece->getAvailableMoves(true);
            for (Move * move : moves) {
                newScore = -getMoveScore(board, move, inverse(color), ++exit, alpha, beta);
                bestScore = min(newScore, bestScore);
                alpha = min(alpha, bestScore);
                if (beta < alpha) break;
            }
            if (beta < alpha) break;
        }
        board->undoMove();
    } else { // Minimize
        bestScore = INT_MIN;
        newScore = INT_MIN;
        
        move->isSimulated = true;
        board->doMove(move);
        
        vector<ChessPiece *> pieces = board->getPiecesByColor(color);
        for (ChessPiece * piece : pieces) {
            vector<Move *> moves = piece->getAvailableMoves(true);
            for (Move * move : moves) {
                newScore = -getMoveScore(board, move, color, ++exit, alpha, beta);
                bestScore = max(newScore, bestScore);

                beta = max(beta, bestScore);
                if (beta < alpha) break;
            }
            if (beta < alpha) break;
        }
        board->undoMove();
    }
    return bestScore;
}

int MinMaxPlayer::getBoardScore(Board * board, PieceColor c) {
    vector<ChessPiece *> friendlyPieces = board->getPiecesByColor(c);
    vector<ChessPiece *> opponentPieces = board->getPiecesByColor(inverse(c));

    long score = evaluateScore(friendlyPieces) - evaluateScore(opponentPieces);
    return score;
}

int MinMaxPlayer::evaluateScore(vector<ChessPiece *> pieces) {
    int materialScore = INT_MIN;
    int locationScore = INT_MIN;
    int movementScore = INT_MIN;
    
    for (ChessPiece * piece : pieces) {
        materialScore += piece->pieceScore;
        locationScore += piece->getLocationScore(piece->location->coordinates.x, piece->location->coordinates.y);
        movementScore += piece->getAvailableSquares(false).size();
    }
    
    if (materialScore < 9900) phase = MIDDLEGAME;
    if (materialScore < 9000) phase = ENDGAME;
    
    int materialFactor = 1;
    int locationFactor = phase == OPENING ? 1 : .25;
    int movementFactor = phase == ENDGAME ? 2 : 1;
    
    long total = materialScore * materialFactor
            + locationScore * locationFactor
            + movementScore * movementFactor;
    return total;
}


