//
// Created by Lukas Bos on 30/11/2017.
// This class provides a backbone for all chess pieces

#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include <SFML/Graphics.hpp>
#include <array>
#include "constants.h"
#include "Square.h"
#include "board.h"

using namespace sf;

class Square;
class Board;
class ChessPiece {
public:
    ChessPiece();
    ChessPiece(Board *board, Square *location, PieceColor color);
    void drawChessPiece(sf::RenderWindow &window);

    void generateImage(PieceType type);

    PieceColor color;
    PieceType type;
    Square *location;
    Board *board;
    bool isCaptured = false;
    int amountOfSteps = 0;

    bool isChecked = false;

    // image utilities
    std::string imageUrlPrefix;
    sf::Image img;
    sf::Texture texture;
    sf::Sprite sprite;

    std::vector<Square *> removeMovesLeadingToSelfCheck(std::vector<Square *> moves, bool considerCheck);

    // functions to be used by subclasses
    virtual std::vector<Square *> getAvailableMoves(bool considerOtherPieces, bool considerCheck);

    virtual int getLocationScore(int x, int y);

    int pieceScore;
    std::array<std::array<int, 8>, 8> locationScores;

    std::vector<Square *> calculateMovesForDirections(
            Square *location,
            Vector2i directions[],
            Board *board,
            PieceColor color,
            short amountOfDirections,
            short maxAmountOfSteps,
            bool considerOtherPieces,
            bool considerCheck
    );
};

#endif //CHESS_CHESSPIECE_H
