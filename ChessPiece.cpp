//
// Created by Lukas Bos on 30/11/2017.
//

#include <iostream>
#include "ChessPiece.h"

using namespace sf;

ChessPiece::ChessPiece(Board *board, Square *location, PieceColor color)
        : board(board), location(location), color(color) {
}

void ChessPiece::drawChessPiece(sf::RenderWindow &window) {
    texture.loadFromImage(img);
    sprite.setTexture(texture, true);
    sprite.setPosition(sf::Vector2f(location->posX + 10, location->posY + 10)); // absolute position
    window.draw(sprite);
}

std::vector<Square *> ChessPiece::getAvailableMoves(bool considerOtherPieces, bool considerCheck) {
    // virtual method for child classes
}

int ChessPiece::getLocationScore(int x, int y) {

    // if we are the topPlayer we must reverse the scores
    if (board->bottomPlayer->color == color) {
        y = 7 - y;
    }

    // check first y then x.
    return locationScores.at(y).at(x);
}

std::vector<Square *>
ChessPiece::calculateMovesForDirections(Square *location, Vector2i directions[], Board *board,
                                        PieceColor color, short amountOfDirections, short maxAmountOfSteps,
                                        bool considerOtherPieces, bool considerCheck) {

    /* considerOtherPieces
     * with considerOtherpieces == true the location of a chesspiece is also stored in the vector
     * Otherwise only the path towards it is stored.
     *
     * ConsiderCheck states if we should check if the moves are valid (thus aren't setting the own king check)
     */


    std::vector<Square *> moves;
    int y = location->coordinates.y;
    int x = location->coordinates.x;

    for (int i = 0; i < amountOfDirections; i++) {
        for (int j = 1; j <= maxAmountOfSteps; j++) {
            int xLocation = x + (j * directions[i].x);
            int yLocation = y + (j * directions[i].y);
            bool elementExists = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;
            if (elementExists) {
                Square *element = board->squares[xLocation][yLocation];
                if (element->chessPiece && element->chessPiece->color == color) {

                    // if we have to check for mate we must be able to travel one further...
                    // todo make names more descirptive
                    if (!considerOtherPieces) {
                        moves.push_back(element);
                    }
                    break;
                } else if (element->chessPiece) {
                    moves.push_back(element);
                    break;
                }
                moves.push_back(element);
            }
        }
    }

    return removeMovesLeadingToSelfCheck(moves, considerCheck);
}

std::vector<Square *>
ChessPiece::removeMovesLeadingToSelfCheck(std::vector<Square *> destinations, bool considerCheck) {
    std::vector<Square *> safeDestinations;
    for (Square *destination : destinations) {
        Move *moveToTry = new Move(location, destination);
        board->doMove(moveToTry);

        if (considerCheck) {
            board->searchForCheckedKing();
        }

        // check if the move results in a situation where it's not check anymore
        for (ChessPiece *piece : board->getPiecesByColor(color)) {

            //todo bug here: isChecked is dependent on moves of other pieces and is prevented when checking other king.
            if (piece->type == KING && !piece->isChecked) {
                safeDestinations.push_back(destination);
            }
        }

        board->undoMove();
    }
    return safeDestinations;
}

void ChessPiece::generateImage(PieceType type) {
    // for the finding images
    std::string names[] = {"King", "Queen", "Rook", "Bishop", "Knight", "Pawn"};
    imageUrlPrefix = color == BLACK ? "Black" : "White";
    img.loadFromFile("images/" + imageUrlPrefix + names[type] + ".png");
}
