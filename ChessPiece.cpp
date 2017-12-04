//
// Created by Lukas Bos on 30/11/2017.
//

#include <iostream>
#include "ChessPiece.h"

using namespace sf;

ChessPiece::ChessPiece(Board *board, GridElement *location, PieceColor color)
        : board(board), location(location), color(color) {
}

void ChessPiece::drawChessPiece(sf::RenderWindow &window) {
    texture.loadFromImage(img);
    sprite.setTexture(texture, true);
    sprite.setPosition(sf::Vector2f(location->posX + 10, location->posY + 10)); // absolute position
    window.draw(sprite);
}

std::vector<GridElement *> ChessPiece::getAvailableMoves() {
    std::vector<GridElement *> availableMoves;

    //TODO refactor this to make it more readable -> maybe use inheritance?

    // Rook
    Vector2i horizontalAndVerticalDirections[] = {
            Vector2i(0, 1),  // Down
            Vector2i(1, 0),  // Right
            Vector2i(0, -1), // Up
            Vector2i(-1, 0)  // Left
    };

    // Bishop
    Vector2i diagonalDirections[] = {
            Vector2i(1, 1),   // Right-Down
            Vector2i(1, -1),  // Right-Up
            Vector2i(-1, -1), // Left-Up
            Vector2i(-1, 1)   // Left-Down
    };

    // Queen and King
    Vector2i allDirections[] = {
            Vector2i(0, 1),   // Down
            Vector2i(1, 0),   // Right
            Vector2i(0, -1),  // Up
            Vector2i(-1, 0),  // Left
            Vector2i(1, 1),   // Right-Down
            Vector2i(1, -1),  // Right-Up
            Vector2i(-1, -1), // Left-Up
            Vector2i(-1, 1)   // Left-Down
    };

    // Knight
    Vector2i knightDirections[] = {
            Vector2i(-2, 1),
            Vector2i(-2, -1),
            Vector2i(-1, 2),
            Vector2i(-1, -2),
            Vector2i(1, 2),
            Vector2i(1, -2),
            Vector2i(2, 1),
            Vector2i(2, -1)
    };


    short y = location->coordinates.y;
    short x = location->coordinates.x;
    if (type == PAWN) {
        bool isBottomColor = board->bottomColor == color;
        short direction = isBottomColor ? -1 : 1;
        availableMoves.push_back(board->elements[x][y + (1 * direction)]);
        if (!hasMoved) {
            availableMoves.push_back(
                    board->elements[x][y + (2 * direction)]);
        }
    } else if (type == ROOK) {
        availableMoves = calculateMovesForDirections(location, horizontalAndVerticalDirections, board, color, 4, 7);
    } else if (type == KNIGHT) {
        availableMoves = calculateMovesForDirections(location, knightDirections, board, color, 8, 1);
    } else if (type == KING) {
        availableMoves = calculateMovesForDirections(location, allDirections, board, color, 8, 1);
    } else if (type == BISHOP) {
        availableMoves = calculateMovesForDirections(location, diagonalDirections, board, color, 4, 7);
    } else if (type == QUEEN) {
        availableMoves = calculateMovesForDirections(location, allDirections, board, color, 8, 7);
    }

    return availableMoves;
}

std::vector<GridElement *>
ChessPiece::calculateMovesForDirections(GridElement *location, Vector2i directions[], Board *board,
                                        PieceColor color, short amountOfDirections, short maxAmountOfSteps) {
    std::vector<GridElement *> moves;
    short y = location->coordinates.y;
    short x = location->coordinates.x;

    for (int i = 0; i < amountOfDirections; i++) {
        for (short j = 1; j <= maxAmountOfSteps; j++) {
            short xLocation = x + (j * directions[i].x);
            short yLocation = y + (j * directions[i].y);
            bool elementExists = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;
            if (elementExists) {
                GridElement *element = board->elements[xLocation][yLocation];
                if (element->chessPiece && element->chessPiece->color == color) {
                    break;
                } else if (element->chessPiece) {
                    moves.push_back(element);
                    break;
                }
                moves.push_back(element);
            }
        }
    }
    return moves;
}

void ChessPiece::generateImage(PieceType type) {
    // for the finding images
    std::string names[] = {"King", "Queen", "Rook", "Bishop", "Knight", "Pawn"};
    imageUrlPrefix = color == BLACK ? "Black" : "White";
    img.loadFromFile("images/" + imageUrlPrefix + names[type] + ".png");
}
