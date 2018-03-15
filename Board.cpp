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
            squares[i][j]->drawSquare(window);
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

        squares[0][row]->setChessPiece(new Rook(this, squares[0][row], color));
        squares[1][row]->setChessPiece(new Knight(this, squares[1][row], color));
        squares[2][row]->setChessPiece(new Bishop(this, squares[2][row], color));
        squares[queenXPosition][row]->setChessPiece(new Queen(this, squares[queenXPosition][row], color));
        squares[kingXPosition][row]->setChessPiece(new King(this, squares[kingXPosition][row], color));
        squares[5][row]->setChessPiece(new Bishop(this, squares[5][row], color));
        squares[6][row]->setChessPiece(new Knight(this, squares[6][row], color));
        squares[7][row]->setChessPiece(new Rook(this, squares[7][row], color));
    }

    // add pawns
    for (int i = 0; i < 8; i++) {
        squares[i][1]->setChessPiece(new Pawn(this, squares[i][1], topPlayer->color));
        squares[i][6]->setChessPiece(new Pawn(this, squares[i][6], bottomPlayer->color));
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
//todo this might later be changed in a function for threats for all pieces
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            ChessPiece *piece = squares[i][j]->chessPiece;
            if (piece) piece->isChecked = false;
        }
    }


    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            ChessPiece *piece = squares[i][j]->chessPiece;
            if (piece) {
                for (Square *square : piece->getAvailableMoves(true, false)) {
                    ChessPiece *pieceToHit = square->chessPiece;
                    if (pieceToHit && pieceToHit->type == KING) {
                        pieceToHit->isChecked = true;
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
                Square *square = squares[i][j];
                if (square->chessPiece && square->chessPiece->color != checkedKing->color) {
                    ChessPiece *piece = square->chessPiece;
                    for (Square *availableMove : piece->getAvailableMoves(true, true)) {
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

void Board::selectSquareFromCoordinates(sf::Vector2i coordinates) {
    selectedSquare->setSelected(false); // set selected property of previous square to false
    selectedSquare = squares[(coordinates.x)][coordinates.y];
    selectedSquare->setSelected(true); // set new square to selected

    focusSquares();
}

void Board::focusSquares() {
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            squares[i][j]->setFocused(false); // there should be no other squares be selected.
        }
    }

    // here check for the squares where the selected square may move to
    if (selectedSquare && selectedSquare->chessPiece) {

        std::vector<Square *> availableMoves;
        availableMoves = selectedSquare->chessPiece->getAvailableMoves(true, true);

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
            squares[i][j] = new Square(i * BLOCK_SIZE, j * BLOCK_SIZE, BLOCK_SIZE, color, coordinates);
        }
    }
}

std::vector<ChessPiece *> Board::getPiecesByColor(PieceColor color) {
    std::vector<ChessPiece *> pieces;
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            Square *square = squares[i][j];

            if (square->chessPiece && square->chessPiece->color == color) {
                pieces.push_back(square->chessPiece);
            }
        }
    }
    return pieces;
}

void Board::checkGameStatus() {
    if (checkedSquare) checkedSquare->isChecked = false;
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