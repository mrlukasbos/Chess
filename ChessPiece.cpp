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
        int direction = isBottomColor ? -1 : 1;
        availableMoves.push_back(board->elements[location->coordinates.x][location->coordinates.y + (1 * direction)]);
        if (!hasMoved) {
            availableMoves.push_back(
                    board->elements[location->coordinates.x][location->coordinates.y + (2 * direction)]);
        }
    } else if (type == ROOK) {
        for (short i = y + 1; i < 8; i++) {
            GridElement *element = board->elements[x][i];
            if (element->chessPiece && element->chessPiece->color == color) {
                break;
            } else if (element->chessPiece) {
                availableMoves.push_back(board->elements[x][i]);
                break;
            }
            availableMoves.push_back(board->elements[x][i]);
        }

        for (short i = y - 1; i >= 0; i--) {
            GridElement *element = board->elements[x][i];
            if (element->chessPiece && element->chessPiece->color == color) {
                break;
            } else if (element->chessPiece) {
                availableMoves.push_back(board->elements[x][i]);
                break;
            }
            availableMoves.push_back(board->elements[x][i]);
        }

        for (short i = x + 1; i < 8; i++) {
            GridElement *element = board->elements[i][y];
            if (element->chessPiece && element->chessPiece->color == color) {
                break;
            } else if (element->chessPiece) {
                availableMoves.push_back(board->elements[i][y]);
                break;
            }
            availableMoves.push_back(board->elements[i][y]);
        }

        for (short i = x - 1; i >= 0; i--) {
            GridElement *element = board->elements[i][y];
            if (element->chessPiece && element->chessPiece->color == color) {
                break;
            } else if (element->chessPiece) {
                availableMoves.push_back(board->elements[i][y]);
                break;
            }
            availableMoves.push_back(board->elements[i][y]);
        }
    } else if (type == KNIGHT) {
        short knight_places_x[] = {-2, -2, -1, -1, 1, 1, 2, 2};
        short knight_places_y[] = {1, -1, 2, -2, 2, -2, 1, -1};

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
    }
    return availableMoves;
}

