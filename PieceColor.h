//
// Created by Lukas Bos on 16/03/2018.
//

#ifndef CHESS_PIECECOLOR_H
#define CHESS_PIECECOLOR_H


enum class PieceColor {
    BLACK, WHITE
};

// returns opposite color
PieceColor inverse(PieceColor const&);

#endif //CHESS_PIECECOLOR_H
