//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_CONSTANTS_H
#define CHESS_CONSTANTS_H

#define BOARD_SIZE 800
#define BLOCK_SIZE BOARD_SIZE/8

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define SELECTION_LINE_THICKNESS 4

// set enumerator for colors of pieces
enum PieceColor {
    BLACK, WHITE
};

enum PieceType {
    KING = 0,
    QUEEN = 1,
    ROOK = 2,
    BISHOP = 3,
    KNIGHT = 4,
    PAWN = 5
};

#endif //CHESS_CONSTANTS_H
