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

    PieceColor color;
    PieceType type;

    GridElement *location;
    Board *board;

    std::string imageUrlPrefix;

    // image utils
    sf::Image img;
    sf::Texture texture;
    sf::Sprite sprite;

    virtual std::vector<GridElement *> getAvailableMoves();

    virtual std::vector<GridElement *> getAvailableMovesWithCheck();

    std::vector<GridElement *>
    calculateMovesForDirections(GridElement *location, Vector2i directions[], Board *board,
                                PieceColor color, short amountOfDirections, short maxAmountOfSteps);

    void generateImage(PieceType type);

    bool isCaptured = false;

    //TODO move this to subclasses
    bool hasMoved = false;
};


#endif //CHESS_CHESSPIECE_H
