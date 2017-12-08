//
// Created by Lukas Bos on 04/12/2017.
//

#include <iostream>
#include "King.h"

King::King(Board *board, GridElement *location, PieceColor color)
        : ChessPiece(board, location, color) {
    type = KING;
    generateImage(type);
}


std::vector<GridElement *> King::getAvailableMoves() {

    //TODO remove check positions from available moves

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

    std::vector<GridElement *> moves;

    short y = location->coordinates.y;
    short x = location->coordinates.x;


    // --- at this part we get all the directions where the king may initially go
    for (int i = 0; i < 8; i++) {
        for (short j = 1; j <= 1; j++) {
            short xLocation = x + (j * allDirections[i].x);
            short yLocation = y + (j * allDirections[i].y);

            bool elementShouldExist = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;

            if (elementShouldExist) {
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


std::vector<GridElement *> King::getAvailableMovesWithCheck() {

    // the elements are pointers but the queue is a copy
    std::vector<GridElement *> allmoves = getAvailableMoves();


    // if iim correct we have the size of moves here.
    for (int i = 0; i < allmoves.size(); i++) {
        // for all grid elements
        for (short k = 0; k < 8; k++) {
            for (short l = 0; l < 8; l++) {
                GridElement *element = board->elements[k][l];
                ChessPiece *piece = element->chessPiece;

                // Get all pieces of the opposite color. This should result in 16 pieces
                if (piece && piece->color != color) {
                    // get the available moves of all pieces
                    // note that we should not check the other king if he can become checked.
                    // This does not matter then.

                    std::vector<GridElement *> coveredLocations = piece->getAvailableMoves();

                    for (int m = 0; m < coveredLocations.size(); m++) {
                        for (int n = 0; n < allmoves.size(); n++) {
                            if (coveredLocations.at(m) == allmoves.at(n)) { // these are references
                                GridElement *elem = allmoves.at(n);
                                allmoves.erase(allmoves.begin() + n);
                            }
                        }
                    }

                }
            }
        }
    }

    return allmoves;
}