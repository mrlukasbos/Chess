//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_CONSTANTS_H
#define CHESS_CONSTANTS_H


// INTERFACE
#define BOARD_SIZE 800
#define BLOCK_SIZE BOARD_SIZE/8
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define SELECTION_LINE_THICKNESS 4


// SCORE SYSTEM USED BY AI
#define KING_SCORE       900
#define QUEEN_SCORE      90
#define ROOKS_CORE       50
#define BISHOP_SCORE     30
#define KNIGHT_SCORE     30
#define PAWN_SCORE       10


// SCORES FOR THE POSITIONS ON THE BOARD
// source: https://chessprogramming.wikispaces.com/Simplified+evaluation+function

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
