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

    PieceType type;
    Board * board;
    Square * location;
    PieceColor color;
    int amountOfSteps = 0;
    bool checked = false;
    bool captured = false;

public:

    /// Initialize a chesspiece
    explicit ChessPiece();

    /// Initialize a chessPiece
    explicit ChessPiece(Board *board, Square *location, PieceColor color);

    /// Returns available squares
    virtual vector<Square *> getAvailableSquares(bool considerCheck) =0;

    /// Returns available moves
    virtual vector<Move *> getAvailableMoves(bool considerCheck);

    /// Get location score (used for the minmaxplayer)
    // TODO  move towards minmaxplayer class
    virtual int getLocationScore(int x, int y);
    int pieceScore;
    std::array<std::array<int, 8>, 8> locationScores;

    // Getters and setters

    // TODO  move towards minmaxplayer class
    int getPieceScore() const;

    // TODO  move towards minmaxplayer class
    void setPieceScore(int pieceScore);

    // TODO  move towards minmaxplayer class
    const array<array<int, 8>, 8>& getLocationScores() const;

    // TODO  move towards minmaxplayer class
    void setLocationScores(const array<array<int, 8>, 8>& locationScores);

    PieceType getType() const;
    void setType(PieceType type);
    Board* getBoard() const;
    void setBoard(Board* board);
    Square* getLocation() const;
    void setLocation(Square* location);
    PieceColor getColor() const;
    void setColor(PieceColor color);
    int getAmountOfSteps() const;
    void setAmountOfSteps(int amountOfSteps);
    bool isChecked() const;
    void setChecked(bool checked);
    bool isCaptured() const;
    void setCaptured(bool captured);
    void increaseAmountOfSteps(int amount);
    void decreaseAmountOfSteps(int amount);
};

#endif //CHESS_CHESSPIECE_H
