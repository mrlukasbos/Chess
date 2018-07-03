//
// Created by Lukas Bos on 11/12/2017.
//

#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <SFML/Graphics.hpp>
#include "PieceColor.h"
#include "Board.h"
#include "Move.h"

using namespace sf;

class Move;
class Board;
class Player {
public:
    /// Initialize the player
    Player();

    /// Initialize player
    explicit Player(PieceColor color);

    /// Returns next move if available, otherwise nullptr
    virtual Move *getNextMove(Board *) =0;

    /// Only used for HumanPlayers.
    virtual void setNextMove(Move *);

    /// Only true for HumanPlayer
    bool isHuman = false;

    /// Return the type of player, which is generally a name
    String getType();

    /// Get the color of the pieces for which the player is playing
    const PieceColor getColor() const;

    /// Sets the color of the pieces of the player
    void setColor(PieceColor);

protected:
    PieceColor color;
    String type;
    Move * nextMove = nullptr;
};


#endif //CHESS_PLAYER_H
