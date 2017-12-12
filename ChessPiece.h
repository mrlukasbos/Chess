//
// Created by Lukas Bos on 30/11/2017.
// This class provides a backbone for all chess pieces

#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include <SFML/Graphics.hpp>
#include "constants.h"
#include "gridElement.h"
#include "board.h"

using namespace sf;

class GridElement;
class Board;
class ChessPiece {
public:
    ChessPiece();
    ChessPiece(Board *board, GridElement *location, PieceColor color);
    void drawChessPiece(sf::RenderWindow &window);

    void generateImage(PieceType type);

    PieceColor color;
    PieceType type;
    GridElement *location;
    Board *board;
    bool isCaptured = false;
    bool hasMoved = false;

    // image utilities
    std::string imageUrlPrefix;
    sf::Image img;
    sf::Texture texture;
    sf::Sprite sprite;

    // functions to be used by subclasses
    virtual std::vector<GridElement *> getAvailableMoves(bool considerOtherPieces);
    virtual std::vector<GridElement *> getAvailableMovesWithCheck();

    int pieceScore;
    int locationScores[64];

    std::vector<GridElement *> calculateMovesForDirections(
            GridElement *location,
            Vector2i directions[],
            Board *board,
            PieceColor color,
            short amountOfDirections,
            short maxAmountOfSteps,
            bool considerOtherPieces
    );
};

#endif //CHESS_CHESSPIECE_H
