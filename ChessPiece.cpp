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
    if (color == BLACK) {
        imageUrlPrefix = "Black";
    } else {
        imageUrlPrefix = "White";
    }

    img.loadFromFile("images/" + imageUrlPrefix + names[type] + ".png");
}

void ChessPiece::drawChessPiece(sf::RenderWindow &window) {

    //It's an example, you have to keep the sf::Texture and sf::Sprite as members of your class
    texture.loadFromImage(img);
    sprite.setTexture(texture, true);
    sprite.setPosition(sf::Vector2f(location->posX + 10, location->posY + 10)); // absolute position
    window.draw(sprite);
}

std::vector<GridElement *> ChessPiece::getAvailableMoves() {
    // decide moves for pawn
    bool isBottomColor = board->bottomColor == color;

    sf::Vector2i nextCoordinates = location->coordinates;

    if (isBottomColor) {
        nextCoordinates.y -= 1;
    } else {
        nextCoordinates.y += 1;
    }

    std::vector<GridElement *> availableMoves;
    availableMoves.push_back(board->elements[nextCoordinates.x][nextCoordinates.y]);

    return availableMoves;
}


/*
 *
 * Let's decide the movesets for each piece here.
 * Let's start with pawn.
 * pawns of bottom color move up
 * pawns of upper color move down
 *
 * What we need in this method:
 *  - Type
 *  - Color
 *  - What color is at the bottom
 */