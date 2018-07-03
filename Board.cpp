/*
 * Board.cpp
 * Created by Lukas Bos on 30/11/2017.
 * Board is where the game is played.
 * Contains: Check, Checkmate, initial positions and allows moves to be set on the board.
*/

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
    bottomPlayer = nullptr;
    topPlayer = nullptr;
    currentPlayer = nullptr;

    // create the squares of the board
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            Color color = (j + i) % 2 == 1 ? Color(100, 100, 100) : Color::White;

            Vector2i coordinates = Vector2i(i, j);
            squares[i][j] = new Square(coordinates);
        }
    }
}

// set all pieces to the initial position
void Board::startGame(Player *bottomPlayer, Player *topPlayer, Player *currentPlayer) {
    this->bottomPlayer = bottomPlayer;
    this->topPlayer = topPlayer;
    this->currentPlayer = currentPlayer;
    initPieces();
}


void Board::initPieces() {
    short kingXPosition = 3, queenXPosition = 4;
    if (topPlayer->color == PieceColor::BLACK) {
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
    // possibly capture a chesspiece
    if (nextMove->endOfMove->chessPiece) {
        nextMove->endOfMove->chessPiece->isCaptured = true;
    }

    if (nextMove->enPassantTakenPiece) {
        nextMove->enPassantTakenPiece->isCaptured = true;
        nextMove->enPassantTakenPiece->location->chessPiece = nullptr;
    }

    // move the chesspiece
    nextMove->endOfMove->chessPiece = nextMove->startOfMove->chessPiece;
    nextMove->startOfMove->chessPiece->location = nextMove->endOfMove;
    nextMove->startOfMove->chessPiece = nullptr;

    nextMove->endOfMove->chessPiece->amountOfSteps++;
    
    if (nextMove->isPromoting) {

        nextMove->endOfMove->chessPiece = nullptr;

        if (currentPlayer->isHuman) {
            while (nextMove->endOfMove->chessPiece == nullptr) {

                std::cout << "make a choice: q -> queen, r -> rook, b -> bishop, n -> knight" << std::endl;
                char PromotionChoice = (char) std::cin.get();

                Square * location = nextMove->endOfMove;
                PieceColor color = nextMove->initialPiece->color;

                switch (PromotionChoice) {
                    case 'q':
                        nextMove->endOfMove->chessPiece = new Queen(this, location, color);
                        break;
                    case 'r':
                        nextMove->endOfMove->chessPiece = new Rook(this, location, color);
                        break;
                    case 'b':
                        nextMove->endOfMove->chessPiece = new Bishop(this, location, color);
                        break;
                    case 'n':
                        nextMove->endOfMove->chessPiece = new Knight(this, location, color);
                        break;
                    default:
                        std::cout << "error in input. make a choice: q -> queen, r -> rook, b -> bishop, n -> knight"
                                  << std::endl;
                }
            }
        } else {
            nextMove->endOfMove->chessPiece = new Queen(this, nextMove->endOfMove, nextMove->initialPiece->color);
        }
    }

    // if there is a castlingRook we must move it also
    if (nextMove->castlingRook) {
        nextMove->rookTargetSquare->chessPiece = nextMove->castlingRook;
        nextMove->castlingRook->location = nextMove->rookTargetSquare;
        nextMove->initalRookSquare->chessPiece = nullptr;
    }
    
    if (!nextMove->isSimulated) {
        cout << nextMove->name << endl;
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

        // if there is a castlingRook we must move undo it also
        if (move->castlingRook) {
            // move rook
            move->initalRookSquare->chessPiece = move->castlingRook;
            move->castlingRook->location = move->initalRookSquare;

            move->rookTargetSquare->chessPiece = nullptr;
        }

        if (move->enPassantTakenPiece) {
            move->enPassantTakenPiece->location->chessPiece = move->enPassantTakenPiece;
        }

        if (!move->isSimulated) {
            cout << "Undo: " << move->name << endl;
        }
    }
}

bool Board::isInCheck(PieceColor color) {
    PieceColor enemyColor = inverse(color);
    for (short i = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            ChessPiece *piece = squares[i][j]->chessPiece;
            if (piece) piece->isChecked = false;
        }
    }

    // check if the enemy has moves that set the king of the chosen color in check
    for (ChessPiece * piece : getPiecesByColor(enemyColor)) {

        //considerotherpieces: true, considerCheck FALSE! otherwise infinite loop.
        for (Square * square : piece->getAvailableSquares(false)) {
            ChessPiece *pieceToHit = square->chessPiece;
            if (pieceToHit && pieceToHit->type == KING && pieceToHit->color == color) {
                pieceToHit->isChecked = true;
                return true;
            }
        }
    }
    return false;
}

bool Board::checkMate() {
    PieceColor color;
    if (isInCheck(PieceColor::WHITE)) color = PieceColor::WHITE;
    else if (isInCheck(PieceColor::BLACK)) color = PieceColor::BLACK;
    else return false;

    // look for all pieces and look if they have available moves
    for (ChessPiece * piece : getPiecesByColor(color)) {
        if (piece->getAvailableSquares(true).size() > 0) {
            return false;
        }
    }
    return true;
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
    if (isInCheck(PieceColor::WHITE) || isInCheck(PieceColor::BLACK)) {
        if (checkMate()) {
            std::string winnerName = isInCheck(PieceColor::WHITE) ? "black" : "white";
            std::cout << "The winner is "  << winnerName << endl ;

            std::cout << "Restart game? Press B to play with Black and press W to play with white" << endl;


            // just start the game again ;-) switch players
            bottomPlayer->color = inverse(bottomPlayer->color);
            topPlayer->color = inverse(topPlayer->color);
            startGame(bottomPlayer, topPlayer, currentPlayer);
        }
    }
}

void Board::setCurrentPlayer(Player *currentPlayer) {
    this->currentPlayer = currentPlayer;
}

Square * Board::getSquare(short x, short y) {
    return squares[x][y];
}
const vector<Move*>& Board::getAllMoves() const {
    return allMoves;
}
