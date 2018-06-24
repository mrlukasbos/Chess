//
// Created by Lukas Bos on 30/11/2017.
//

#ifndef CHESS_CONSTANTS_H
#define CHESS_CONSTANTS_H


// INTERFACE
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define GAME_SIZE 800
#define BOARD_BORDER_THICKNESS 40
#define BOARD_SIZE (GAME_SIZE - 2 * BOARD_BORDER_THICKNESS)
#define BLOCK_SIZE BOARD_SIZE/8
#define SELECTION_LINE_THICKNESS 4

// SCORE SYSTEM USED BY AI
#define KING_SCORE       1000
#define QUEEN_SCORE      900
#define ROOK_SCORE       500
#define BISHOP_SCORE     330
#define KNIGHT_SCORE     320
#define PAWN_SCORE       100


// SCORES FOR THE POSITIONS ON THE BOARD
// source: https://chessprogramming.wikispaces.com/Simplified+evaluation+function

enum PieceType {
    KING = 0,
    QUEEN = 1,
    ROOK = 2,
    BISHOP = 3,
    KNIGHT = 4,
    PAWN = 5
};

#endif //CHESS_CONSTANTS_H
