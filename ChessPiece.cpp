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

    if (type == PAWN) {
        bool isBottomColor = board->bottomColor == color;
        int direction = isBottomColor ? -1 : 1;
        availableMoves.push_back(board->elements[location->coordinates.x][location->coordinates.y + (1 * direction)]);
        if (!hasMoved) {
            availableMoves.push_back(
                    board->elements[location->coordinates.x][location->coordinates.y + (2 * direction)]);
        }
    } else if (type == ROOK) {
        for (int i = 0; i < 8; i++) {
            if (location->coordinates.y != i) {
                availableMoves.push_back(board->elements[location->coordinates.x][i]);
            }
            if (location->coordinates.x != i) {
                availableMoves.push_back(board->elements[i][location->coordinates.y]);
            }
        }

    }
    return availableMoves;
}
