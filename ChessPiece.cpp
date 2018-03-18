//
// Created by Lukas Bos on 30/11/2017.
//

#include <iostream>
#include "ChessPiece.h"

using namespace sf;

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

void ChessPiece::drawChessPiece(sf::RenderWindow &window) {
    texture.loadFromImage(img);
    texture.setSmooth(true);
    sprite.setScale(0.9, 0.9);
    sprite.setTexture(texture, true);
    sprite.setPosition(sf::Vector2f(location->posX + 10, location->posY + 10)); // absolute position
    window.draw(sprite);
}

std::vector<Move *> ChessPiece::getAvailableMoves(bool considerCheck) {
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

/*
 * This function takes an array of directional vectors (sf::vector21)
 * For example: (1,1) means up-right and (-1,0) means left.
 * It returns the available legal moves according to the board.
 * Considercheck is usually always true, but it is needed for the program to detect check(mate)
 */

std::vector<Move *>
ChessPiece::calculateMovesForDirections(Square *location, Vector2i directions[], Board *board,
                                        PieceColor color, short amountOfDirections, short maxAmountOfSteps,
                                        bool considerCheck) {

    std::vector<Move *> moves;
    int y = location->coordinates.y;
    int x = location->coordinates.x;

    for (int i = 0; i < amountOfDirections; i++) {
        for (int j = 1; j <= maxAmountOfSteps; j++) {
            int xLocation = x + (j * directions[i].x);
            int yLocation = y + (j * directions[i].y);
            bool elementExists = xLocation >= 0 && xLocation < 8 && yLocation >= 0 && yLocation < 8;
            if (elementExists) {
                Square *targetSquare = board->squares[xLocation][yLocation];
                Move * move = new Move(board, location, targetSquare);
                if (targetSquare->chessPiece && targetSquare->chessPiece->color == color) {
                    break;
                } else if (targetSquare->chessPiece) {
                    moves.push_back(move);
                    break;
                }
                moves.push_back(move);
            }
        }
    }

    if (considerCheck) {
        return removeMovesLeadingToSelfCheck(moves);
    }
    return moves;
}

std::vector<Move *>
ChessPiece::removeMovesLeadingToSelfCheck(std::vector<Move *> moves) {
    std::vector<Move *> safeMoves;
    for (Move *moveToTry : moves) {
        moveToTry->isSimulated = true;
        board->doMove(moveToTry);

        if (!board->isInCheck(color)){
            safeMoves.push_back(moveToTry);
        }

        board->undoMove();
    }
    return safeMoves;
}

void ChessPiece::generateImage(PieceType type) {
    // for the finding images
    std::string names[] = {"King", "Queen", "Rook", "Bishop", "Knight", "Pawn"};
    imageUrlPrefix = color == PieceColor::BLACK ? "Black" : "White";
    img.loadFromFile("images/" + imageUrlPrefix + names[type] + ".png");
}
