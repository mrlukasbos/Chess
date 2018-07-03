//
// Created by Lukas Bos on 30/11/2017.
// This class provides a backbone for all chess pieces

#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include <SFML/Graphics.hpp>
#include <array>
#include "constants.h"
#include "Square.h"
#include "Board.h"
#include "PieceColor.h"

using namespace sf;
using namespace std;

class Square;
class Move;
class Board;
class ChessPiece {
public:
    ChessPiece();
    ChessPiece(Board *board, Square *location, PieceColor color);

    PieceType type;
    Board * board;
    Square * location;
    PieceColor color;
    int amountOfSteps = 0;
    bool isChecked = false;
    bool isCaptured = false;

    virtual std::vector<Square *> getAvailableSquares(bool considerCheck) =0;
    virtual std::vector<Move *> getAvailableMoves(bool considerCheck);

    virtual int getLocationScore(int x, int y);
    int pieceScore;
    std::array<std::array<int, 8>, 8> locationScores;

protected:
    std::vector<Square *> removeMovesLeadingToSelfCheck(vector<Square *> moves);

    std::vector<Square *> calculateMovesForDirections(
            Square *location,
            Vector2i directions[],
            Board *board,
            PieceColor color,
            short amountOfDirections,
            short maxAmountOfSteps,
            bool considerCheck
    );
};

#endif //CHESS_CHESSPIECE_H
