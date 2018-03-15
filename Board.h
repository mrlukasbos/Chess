//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "Square.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Player;
class Square;

class ChessPiece;
class Move;
class Board {
public:
    Board();

    // constructs a board from an existing board (copies the board)
    Board(Board const &) = default;
    Square *squares[8][8];

    void drawBoard(sf::RenderWindow &window);
    void startGame(Player *bottomPlayer, Player *topPlayer);
    void selectSquareFromCoordinates(Vector2i coordinates);
    void focusSquares();

    void doMove(Move *nextMove);

    void undoMove();

    std::vector<Move *> allMoves;

    // there can be only one checked king.
    ChessPiece *checkedKing;
    void checkGameStatus();

    Square * selectedSquare;
    Square *checkedSquare;
    Player *bottomPlayer;
    Player *topPlayer;
    std::vector<ChessPiece *> getPiecesByColor(PieceColor color);

    void searchForCheckedKing();

    bool checkMate();
private:
    void createBoard();
    void drawPiecesOnBoard();
};


#endif //CHESS_BOARD_H
