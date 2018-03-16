//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "Square.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "PieceColor.h"

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

    ChessPiece *checkedKing;
    void checkGameStatus();

    Square * selectedSquare;
    Player *bottomPlayer;
    Player *topPlayer;
    std::vector<ChessPiece *> getPiecesByColor(PieceColor color);

    bool isInCheck(PieceColor color);

    bool checkMate();
private:
    void createBoard();
    void initPieces();
};


#endif //CHESS_BOARD_H
