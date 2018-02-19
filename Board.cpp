//
// Created by Lukas Bos on 30/11/2017.
//

#include <iostream>
#include "Board.h"
#include "chesspieces/Rook.h"
#include "chesspieces/Bishop.h"
#include "chesspieces/Knight.h"
#include "chesspieces/Pawn.h"
#include "chesspieces/Queen.h"
#include "chesspieces/King.h"

using namespace sf;

Board::Board() {
    createBoard();
}

void Board::drawBoard(sf::RenderWindow &window) {
    for (short i  = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            elements[i][j]->drawGridElement(window);
        }
    }
}

// set all pieces to the initial position
void Board::startGame(Player *bottomPlayer, Player *topPlayer) {
    this->bottomPlayer = bottomPlayer;
    this->topPlayer = topPlayer;

    createBoard();
    drawPiecesOnBoard();
}


void Board::drawPiecesOnBoard() {
    short kingXPosition = 3, queenXPosition = 4;
    if (topPlayer->color == BLACK) {
        kingXPosition = 4;
        queenXPosition = 3;
    }

    // make all pieces twice
    for (int i = 0; i < 2; i++) {
        PieceColor color = topPlayer->color;
        short row = 0;

        if (i == 1) {
            color = bottomPlayer->color;
            row = 7;
        }

        elements[0][row]->setChessPiece(new Rook(this, elements[0][row], color));
        elements[1][row]->setChessPiece(new Knight(this, elements[1][row], color));
        elements[2][row]->setChessPiece(new Bishop(this, elements[2][row], color));
        elements[queenXPosition][row]->setChessPiece(new Queen(this, elements[queenXPosition][row], color));
        elements[kingXPosition][row]->setChessPiece(new King(this, elements[kingXPosition][row], color));
        elements[5][row]->setChessPiece(new Bishop(this, elements[5][row], color));
        elements[6][row]->setChessPiece(new Knight(this, elements[6][row], color));
        elements[7][row]->setChessPiece(new Rook(this, elements[7][row], color));
    }

    // add pawns
    for (int i = 0; i < 8; i++) {
        elements[i][1]->setChessPiece(new Pawn(this, elements[i][1], topPlayer->color));
        elements[i][6]->setChessPiece(new Pawn(this, elements[i][6], bottomPlayer->color));
    }

}

void Board::doMove(Move *nextMove) {
    if (nextMove) {

        // possibly capture a chesspiece
        if (nextMove->endOfMove->chessPiece) {
            nextMove->endOfMove->chessPiece->isCaptured = true;
        }

        // move the chesspiece
        nextMove->endOfMove->chessPiece = nextMove->startOfMove->chessPiece;
        nextMove->startOfMove->chessPiece->location = nextMove->endOfMove;
        nextMove->startOfMove->chessPiece = NULL;

        nextMove->endOfMove->chessPiece->amountOfSteps++;
    }

    allMoves.push_back(nextMove);
}

void Board::undoMove() {
    Move *move = allMoves.back();

    if (move) {
        allMoves.pop_back();
        // revive a piece when it was taken
        if (move->takenPiece) {
            move->takenPiece->isCaptured = false;
            move->takenPiece->location = move->endOfMove;
        }
        move->endOfMove->chessPiece = move->takenPiece;

        move->initialPiece->location = move->startOfMove;
        move->startOfMove->chessPiece = move->initialPiece;
        move->initialPiece->amountOfSteps--;

    }
}

void Board::searchForCheckedKing() {

    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            ChessPiece *piece = elements[i][j]->chessPiece;
            if (piece) {
                for (GridElement *element : piece->getAvailableMoves(true, false)) {
                    ChessPiece *pieceToHit = element->chessPiece;
                    if (pieceToHit && pieceToHit->type == KING && pieceToHit->color != piece->color) {
                        checkedGridElement = pieceToHit->location;
                        checkedGridElement->isChecked = true;
                        checkedKing = pieceToHit;
                    }
                }
            }
        }
    }
}

bool Board::checkMate() {
    // todo check if this function still works
    if (checkedKing) {
        for (short i = 0; i < 8; i++) {
            for (short j = 0; j < 8; j++) {
                GridElement *element = elements[i][j];
                if (element->chessPiece && element->chessPiece->color != checkedKing->color) {
                    ChessPiece *piece = element->chessPiece;
                    for (GridElement *availableMove : piece->getAvailableMoves(true, true)) {
                        Move *moveToTry = new Move(piece->location, availableMove);
                        doMove(moveToTry);
                        if (!checkedKing) {
                            undoMove();
                            return false;
                        }
                        undoMove();
                    }
                }
            }
        }
        return true;
    }

    return false;
}

void Board::selectGridElementFromCoordinates(sf::Vector2i coordinates) {
    selectedGridElement->setSelected(false); // set selected property of previous element to false
    selectedGridElement = elements[(coordinates.x)][coordinates.y];
    selectedGridElement->setSelected(true); // set new element to selected

    focusGridElements();
}

void Board::focusGridElements() {
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            elements[i][j]->setFocused(false); // there should be no other elements be selected.
        }
    }

    // here check for the elements where the selected element may move to
    if (selectedGridElement && selectedGridElement->chessPiece) {

        std::vector<GridElement *> availableMoves;
        availableMoves = selectedGridElement->chessPiece->getAvailableMoves(true, true);

        for (int i = 0; i < availableMoves.size(); i++) {
            availableMoves.at(i)->setFocused(true);
        }
    }
}

void Board::createBoard() {
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            Color color = (j + i) % 2 == 1 ? Color(100, 100, 100) : Color::White;

            sf::Vector2i coordinates = sf::Vector2i(i, j);
            elements[i][j] = new GridElement(i * BLOCK_SIZE, j * BLOCK_SIZE, BLOCK_SIZE, color, coordinates);
        }
    }
}

std::vector<ChessPiece *> Board::getPiecesByColor(PieceColor color) {
    std::vector<ChessPiece *> pieces;
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            GridElement *element = elements[i][j];

            if (element->chessPiece && element->chessPiece->color == color) {
                pieces.push_back(element->chessPiece);
            }
        }
    }
    return pieces;
}

void Board::checkGameStatus() {
    if (checkedGridElement) checkedGridElement->isChecked = false;
    checkedKing = NULL;

    searchForCheckedKing();

    if (checkedKing) {
        if (checkMate()) {
            std::cout << "We have a winner! \n";
        } else {
            std::cout << "Check! \n";
        }
    }
}