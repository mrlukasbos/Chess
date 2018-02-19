//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "GridElement.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Player;
class GridElement;

class ChessPiece;
class Move;
class Board {
public:
    Board();

    // constructs a board from an existing board (copies the board)
    Board(Board const &) = default;
    GridElement *elements[8][8];

    void drawBoard(sf::RenderWindow &window);
    void startGame(Player *bottomPlayer, Player *topPlayer);
    void selectGridElementFromCoordinates(Vector2i coordinates);
    void focusGridElements();

    void doMove(Move *nextMove);

    void undoMove();

    std::vector<Move *> allMoves;


    void checkGameStatus();

    GridElement * selectedGridElement;
    Player *bottomPlayer;
    Player *topPlayer;
    std::vector<ChessPiece *> getPiecesByColor(PieceColor color);

    ChessPiece *checkedKing();

    bool checkMate();
private:
    void createBoard();
    void drawPiecesOnBoard();
};


#endif //CHESS_BOARD_H
