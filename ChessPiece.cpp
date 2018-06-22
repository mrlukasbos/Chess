//
// Created by Lukas Bos on 30/11/2017.
//

#include <iostream>
#include "ChessPiece.h"

using namespace sf;
using namespace std;

ChessPiece::ChessPiece() {
    pieceScore = 0;
    type = PAWN;
};

ChessPiece::ChessPiece(Board *board, Square *location, PieceColor color)
        : board(board), location(location), color(color) {

    // type and piecescore is defined in the subclasses.
    pieceScore = 0;
    type = PAWN;
}

void ChessPiece::drawChessPiece(RenderWindow &window) {
    texture.loadFromImage(img);
    texture.setSmooth(true);
    sprite.setScale(0.9, 0.9);
    sprite.setTexture(texture, true);
    sprite.setPosition(Vector2f(location->posX + 10, location->posY + 10)); // absolute position
    window.draw(sprite);
}

vector<Move *> ChessPiece::getAvailableMoves(bool considerCheck) {
    vector<Move *> moves;
    for (Square * square : getAvailableSquares(considerCheck)) {
        moves.push_back(new Move(board, location, square));
    }
    return moves;
}

int ChessPiece::getLocationScore(int x, int y) {

    // if we are the topPlayer we must reverse the scores
    if (board->bottomPlayer->color == color) {
        y = 7 - y;
    }

    // check first y then x.
    return locationScores.at(y).at(x);
}

/*
 * This function takes an array of directional vectors (sf::vector21)
 * For example: (1,1) means up-right and (-1,0) means left.
 * It returns the available legal moves according to the board.
 * Considercheck is usually always true, but it is needed for the program to detect check(mate)
 */

vector<Square *>
ChessPiece::calculateMovesForDirections(Square *location, Vector2i directions[], Board *board,
                                        PieceColor color, short amountOfDirections, short maxAmountOfSteps,
                                        bool considerCheck) {

    vector<Square *> moves;
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
                    break;
                } else if (element->chessPiece) {
                    moves.push_back(element);
                    break;
                }
                moves.push_back(element);
            }
        }
    }

    if (considerCheck) {
        return removeMovesLeadingToSelfCheck(moves);
    }
    return moves;
}

vector<Square *>
ChessPiece::removeMovesLeadingToSelfCheck(vector<Square *> destinations) {
    vector<Square *> safeDestinations;
    for (Square *destination : destinations) {
        Move *moveToTry = new Move(board, location, destination, true);
        board->doMove(moveToTry);

        if (!board->isInCheck(color)){
          safeDestinations.push_back(destination);
        }

        board->undoMove();
        delete moveToTry;
    }
    return safeDestinations;
}

void ChessPiece::generateImage(PieceType type) {
    // for the finding images
    std::string names[] = {"King", "Queen", "Rook", "Bishop", "Knight", "Pawn"};
    imageUrlPrefix = color == PieceColor::BLACK ? "Black" : "White";
    img.loadFromFile("images/" + imageUrlPrefix + names[type] + ".png");
}
