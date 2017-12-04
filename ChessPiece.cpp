//
// Created by Lukas Bos on 30/11/2017.
//

#include <iostream>
#include "ChessPiece.h"

ChessPiece::ChessPiece(Board *board, GridElement *location, PieceColor color, PieceType type) : board(board),
                                                                                                location(location),
                                                                                                color(color),
                                                                                                type(type) {
    // for the finding images
    std::string names[] = {"King", "Queen", "Rook", "Bishop", "Knight", "Pawn"};
    imageUrlPrefix = color == BLACK ? "Black" : "White";
    img.loadFromFile("images/" + imageUrlPrefix + names[type] + ".png");
}

void ChessPiece::drawChessPiece(sf::RenderWindow &window) {
    texture.loadFromImage(img);
    sprite.setTexture(texture, true);
    sprite.setPosition(sf::Vector2f(location->posX + 10, location->posY + 10)); // absolute position
    window.draw(sprite);
}

std::vector<GridElement *> ChessPiece::getAvailableMoves() {
    std::vector<GridElement *> availableMoves;

    //TODO refactor this to make it more readable

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
        short amountOfDirections = 4;
        short rook_directions_x[] = {0, 1, 0, -1};
        short rook_directions_y[] = {1, 0, -1, 0};
        availableMoves = calculateMovesForDirections(location, rook_directions_x, rook_directions_y, board, color, 7,
                                                     amountOfDirections);
    } else if (type == KNIGHT) {
        short amountOfDirections = 8;
        short knight_places_x[] = {-2, -2, -1, -1, 1, 1, 2, 2};
        short knight_places_y[] = {1, -1, 2, -2, 2, -2, 1, -1};
        availableMoves = calculateMovesForDirections(location, knight_places_x, knight_places_y, board, color, 1,
                                                     amountOfDirections);
    } else if (type == KING) {
        short amountOfDirections = 8;
        short king_places_x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        short king_places_y[] = {1, 0, -1, 1, -1, 1, 0, -1};
        availableMoves = calculateMovesForDirections(location, king_places_x, king_places_y, board, color, 1,
                                                     amountOfDirections);
    } else if (type == BISHOP) {
        short amountOfDirections = 4;
        short bishop_directions_x[] = {1, 1, -1, -1};
        short bishop_directions_y[] = {1, -1, 1, -1};
        availableMoves = calculateMovesForDirections(location, bishop_directions_x, bishop_directions_y, board, color,
                                                     7, amountOfDirections);
    } else if (type == QUEEN) {
        short amountOfDirections = 8;
        short queen_directions_x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        short queen_directions_y[] = {1, 0, -1, 1, -1, 1, 0, -1};
        availableMoves = calculateMovesForDirections(location, queen_directions_x, queen_directions_y, board, color, 7,
                                                     amountOfDirections);
    }

    return availableMoves;
}

std::vector<GridElement *>
ChessPiece::calculateMovesForDirections(GridElement *location, short XDirections[], short YDirections[], Board *board,
                                        PieceColor color, short maxAmountOfSteps, short amountOfDirections) {
    std::vector<GridElement *> moves;
    short y = location->coordinates.y;
    short x = location->coordinates.x;

    for (int i = 0; i < amountOfDirections; i++) {
        for (short j = 1; j <= maxAmountOfSteps; j++) {
            short xLocation = x + (j * XDirections[i]);
            short yLocation = y + (j * YDirections[i]);
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

