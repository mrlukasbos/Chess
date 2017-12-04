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

        // rook can go in 4 directions
        short rook_directions_x[] = {0, 1, 0, -1};
        short rook_directions_y[] = {1, 0, -1, 0};

        for (int i = 0; i < 5; i++) {

            // bishop can maximally move 8 places
            for (short j = 1; j < 8; j++) {
                short xLocation = x + j * rook_directions_x[i];
                short yLocation = y + j * rook_directions_y[i];

                bool elementExists = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;
                if (elementExists) {
                    GridElement *element = board->elements[xLocation][yLocation];
                    if (element->chessPiece && element->chessPiece->color == color) {
                        break;
                    } else if (element->chessPiece) {
                        availableMoves.push_back(element);
                        break;
                    }
                    availableMoves.push_back(element);
                }

            }
        }
    } else if (type == KNIGHT) {
        short knight_places_x[] = {-2, -2, -1, -1, 1, 1, 2, 2};
        short knight_places_y[] = {1, -1, 2, -2, 2, -2, 1, -1};
        // knight can move to 8 places
        for (short i = 0; i < 9; i++) {
            short xLocation = x + knight_places_x[i];
            short yLocation = y + knight_places_y[i];

            bool elementExists = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;
            if (elementExists) {
                GridElement *element = board->elements[xLocation][yLocation];
                bool elementIsOccupied = element->chessPiece && element->chessPiece->color == color;

                if (!elementIsOccupied) {
                    availableMoves.push_back(element);
                }
            }

        }
    } else if (type == KING) {

        short king_places_x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        short king_places_y[] = {1, 0, -1, 1, -1, 1, 0, -1};

        // king can move to 8 places
        for (short i = 0; i < 9; i++) {
            short xLocation = x + king_places_x[i];
            short yLocation = y + king_places_y[i];

            bool elementExists = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;
            if (elementExists) {
                GridElement *element = board->elements[xLocation][yLocation];
                bool elementIsOccupied = element->chessPiece && element->chessPiece->color == color;

                if (!elementIsOccupied) {
                    availableMoves.push_back(element);
                }
            }

        }
    } else if (type == BISHOP) {

        short bishopXDirections[] = {1, 1, -1, -1};
        short bishopYDirections[] = {1, -1, 1, -1};

        //bishop can walk in 4 directions
        for (int i = 0; i < 4; i++) {

            // bishop can maximally move 8 places
            for (short j = 1; j < 7; j++) {
                short xLocation = x + j * bishopXDirections[i];
                short yLocation = y + j * bishopYDirections[i];

                bool elementExists = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;
                if (elementExists) {
                    GridElement *element = board->elements[xLocation][yLocation];
                    if (element->chessPiece && element->chessPiece->color == color) {
                        break;
                    } else if (element->chessPiece) {
                        availableMoves.push_back(element);
                        break;
                    }
                    availableMoves.push_back(element);
                }

            }
        }
    } else if (type == QUEEN) {

        // queen can go in 8 directions
        short queen_directions_x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        short queen_directions_y[] = {1, 0, -1, 1, -1, 1, 0, -1};

        for (int i = 0; i < 9; i++) {

            // bishop can maximally move 8 places
            for (short j = 1; j < 8; j++) {
                short xLocation = x + j * queen_directions_x[i];
                short yLocation = y + j * queen_directions_y[i];

                bool elementExists = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;
                if (elementExists) {
                    GridElement *element = board->elements[xLocation][yLocation];
                    if (element->chessPiece && element->chessPiece->color == color) {
                        break;
                    } else if (element->chessPiece) {
                        availableMoves.push_back(element);
                        break;
                    }
                    availableMoves.push_back(element);
                }

            }
        }
    }
    return availableMoves;
}

