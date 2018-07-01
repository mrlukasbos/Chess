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
using namespace std;

class Player;
class Square;

class ChessPiece;
class Move;
class Board {
public:

    Board(RenderWindow &window);
    
    /// Constructs a board from an existing board (copies the board)
    Board(Board const &) = default;
    
    
    Square *squares[8][8];

    void drawBoard();
    void startGame(Player *bottomPlayer, Player *topPlayer, Player * currentPlayer);
    void selectSquareFromCoordinates(Vector2i coordinates);
    void focusSquares();

    void doMove(Move *nextMove);
    void setCurrentPlayer(Player *currentPlayer);
    void undoMove();

    /// return the vector of all moves that were done.
    vector<Move *> allMoves;

    /// Checks if a color is in check and if there is checkmate
    void checkGameStatus();

    /// a square being selected by a Humanplayer
    Square * selectedSquare;
    
    /// The player at the bottom of the board
    Player *bottomPlayer;
    
    /// The player at the top of the board
    Player *topPlayer;
    
    /// The player which is to move next
    Player *currentPlayer;
    
    /// Return a vector of chesspieces by color
    vector<ChessPiece *> getPiecesByColor(PieceColor color);

    /// checks if the given color is in check on the board.
    bool isInCheck(PieceColor color);
    
    /// checks if there is a checkmate on the board. Use isInCheck() to view which color is checkmated.
    bool checkMate();
private:
    void createBoard();
    void initPieces();
    RenderWindow &window;
};


#endif //CHESS_BOARD_H
