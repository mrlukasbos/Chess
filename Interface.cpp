//
// Created by Lukas Bos on 19/02/2018.
//

#include "Interface.h"

using namespace sf;

Interface::Interface(Board * board, RenderWindow &window) : board(board), window(window) {
    font.loadFromFile("OpenSans-Regular.ttf");
    boldFont.loadFromFile("OpenSans-Bold.ttf");
}

void Interface::draw() {
    window.clear(Color(200, 200, 200));
    drawBoard();
}

void Interface::drawBoard() {
    RectangleShape boardBackground;
    boardBackground.setPosition(10, 10);
    boardBackground.setSize(sf::Vector2f(GAME_SIZE -20, GAME_SIZE -20));
    boardBackground.setFillColor(boardBackgroundColor);
    window.draw(boardBackground);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            RectangleShape square;
            if ((i+j)%2 == 0) {
                square.setFillColor(lightSquareColor);
            } else {
                square.setFillColor(darkSquareColor);
            }
            square.setPosition(BOARD_BORDER_THICKNESS + i * BLOCK_SIZE, BOARD_BORDER_THICKNESS + j * BLOCK_SIZE);
            square.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
            window.draw(square);
        }
    }
}

void Interface::drawPieces() {

}

//void Interface::showCurrentPlayerText(Player *currentPlayer) {
//    Text currentMoveText("Current move", font, 26);
//    currentMoveText.setFillColor(Color::Black);
//    currentMoveText.setCharacterSize(24);
//    currentMoveText.setPosition(GAME_SIZE + 40, WINDOW_HEIGHT / 2 - 50);
//
//    Text currentColorToMoveName(currentPlayer->color == PieceColor::BLACK ? "Black" : "White", boldFont, 26);
//    currentColorToMoveName.setFillColor(Color::Black);
//    currentColorToMoveName.setCharacterSize(48);
//    currentColorToMoveName.setPosition(GAME_SIZE + 40, WINDOW_HEIGHT / 2 - 20);
//
//    window.draw(currentMoveText);
//    window.draw(currentColorToMoveName);
//}


//void Interface::showPlayerTypes() {
//    Text topPlayerTypeText(board.topPlayer->getType(), font, 26);
//    topPlayerTypeText.setFillColor(Color::Black);
//    topPlayerTypeText.setCharacterSize(24);
//    topPlayerTypeText.setPosition(GAME_SIZE + 40, 40);
//
//    Text bottomPlayerTypeText(board.bottomPlayer->getType(), font, 26);
//    bottomPlayerTypeText.setFillColor(Color::Black);
//    bottomPlayerTypeText.setCharacterSize(24);
//    bottomPlayerTypeText.setPosition(GAME_SIZE + 40, WINDOW_HEIGHT - 80);
//
//    window.draw(topPlayerTypeText);
//    window.draw(bottomPlayerTypeText);
//};
//
//void Interface::showCoordinates() {
//    char letters[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
//
//    for (short i = 0; i<8; i++) {
//        Text coordinateNumberPart(std::to_string(8-i), boldFont, 18);
//        Text coordinateLetterPart(letters[i], boldFont, 18);
//
//        coordinateLetterPart.setFillColor(Color::White);
//        coordinateLetterPart.setCharacterSize(20);
//        coordinateLetterPart.setPosition(BOARD_BORDER_THICKNESS + 40 + (i * BLOCK_SIZE), GAME_SIZE - 40);
//
//        coordinateNumberPart.setFillColor(Color::White);
//        coordinateNumberPart.setCharacterSize(20);
//        coordinateNumberPart.setPosition(15, BOARD_BORDER_THICKNESS + 40 + (i * BLOCK_SIZE));
//
//        window.draw(coordinateLetterPart);
//        window.draw(coordinateNumberPart);
//    }
//}
//
//void Interface::showLoadingText() {
//    Text thinkText("The computer is thinking...", font, 26);
//    thinkText.setFillColor(Color::Blue);
//    thinkText.setCharacterSize(24);
//    thinkText.setPosition(GAME_SIZE + 40, 100);
//
//    window.draw(thinkText);
//}


//void drawNextMoveOnBoard(RenderWindow &w, Player * cp, Interface i, Board b) {
//    w.clear(menuColor);
//    i.showBoardBackground();
//    b.drawBoard(); // this is where the redraw of the board happens
//    i.showCurrentPlayerText(cp);
//    i.showPlayerTypes();
//    i.showCoordinates();
//    i.showSelectedSquareName();
//    updateWindowNextCycle = false;
//}


//
//Move *HumanPlayer::getNextMove(Board *board) {
//    if (Mouse::isButtonPressed(Mouse::Left)) {
//        return DetermineMoveFromMousePos(board, Mouse::getPosition(window).x, Mouse::getPosition(window).y);
//    }
//
//    return nullptr;
//}
//
//Move *HumanPlayer::DetermineMoveFromMousePos(Board *board, int x, int y) {
//
//    // for all squares
//    for (short i = 0; i < 8; i++) {
//        for (short j = 0; j < 8; j++) {
//            Square *square = board->squares[i][j];
//            square->setSelected(false); // there should be no other squares be selected.
//
//            bool squareIsClicked = x > square->posX && x < square->posX + BLOCK_SIZE
//                                   && y > square->posY && y < square->posY + BLOCK_SIZE;
//
//            if (squareIsClicked) {
//
//                // here a bug occured
//                // It appears that when a square was focussed and a move was done, the square is being focussed until the next draw.
//                // still it wanted to do the move when the press was taking long. but then the chesspiece was already moved...
//                // todo fix this neatly. (selection of squares etc)
//                if (square->isFocused && board->selectedSquare->chessPiece) {
//                    for (Move * move : board->selectedSquare->chessPiece->getAvailableMoves(true)) {
//                        // we found the move we want to do in the list of available moves of the piece!
//                        // we need this method because we must look up if it is legal and if it is castling.
//                        if (move->endOfMove == square) {
//                            return move;
//                        }
//                    }
//
//                    // return new Move(board, board->selectedSquare, square);
//                } else if (square->chessPiece && square->chessPiece->color == this->color) {
//                    square->setSelected(true);
//                    board->selectedSquare = square;
//                }
//            }
//        }
//    }
//
//    board->focusSquares();
//    return nullptr;
//}
//

//
//
//void Square::drawSquare(sf::RenderWindow &window) {
//
//    rectangle.setPosition(posX + SELECTION_LINE_THICKNESS, posY + SELECTION_LINE_THICKNESS);
//    rectangle.setSize(sf::Vector2f(size - 2*SELECTION_LINE_THICKNESS, size - 2*SELECTION_LINE_THICKNESS));
//    rectangle.setOutlineThickness(SELECTION_LINE_THICKNESS);
//
//    if (isSelected) {
//        rectangle.setOutlineColor(sf::Color::Blue);
//    } else if (isFocused && chessPiece) {
//        rectangle.setOutlineColor(sf::Color::Red);
//    } else if (isFocused) {
//        rectangle.setOutlineColor(sf::Color::Green);
//    } else if (isChecked) {
//        rectangle.setOutlineColor(sf::Color::Yellow);
//    } else {
//        rectangle.setOutlineColor(color);
//    }
//
//    rectangle.setFillColor(color);
//    window.draw(rectangle);
//
//    if (chessPiece) {
//        chessPiece->drawChessPiece(window);
//    }
//}


//
//void ChessPiece::generateImage(PieceType type) {
//    // for the finding images
//    std::string names[] = {"King", "Queen", "Rook", "Bishop", "Knight", "Pawn"};
//    imageUrlPrefix = color == PieceColor::BLACK ? "Black" : "White";
//    img.loadFromFile("images/" + imageUrlPrefix + names[type] + ".png");
//}
//
//void ChessPiece::drawChessPiece(RenderWindow &window) {
//    texture.loadFromImage(img);
//    texture.setSmooth(true);
//    sprite.setScale(0.9, 0.9);
//    sprite.setTexture(texture, true);
//    sprite.setPosition(Vector2f(location->posX + 10, location->posY + 10)); // absolute position
//    window.draw(sprite);
//}


//
//void Board::selectSquareFromCoordinates(sf::Vector2i coordinates) {
//    if (selectedSquare){
//        selectedSquare->setSelected(false); // set selected property of previous square to false
//    }
//    selectedSquare = squares[(coordinates.x)][coordinates.y];
//    selectedSquare->setSelected(true); // set new square to selected
//
//    focusSquares();
//}
//
//void Board::focusSquares() {
//    for (short i = 0; i < 8; i++) {
//        for (short j = 0; j < 8; j++) {
//            squares[i][j]->setFocused(false); // there should be no other squares be selected.
//        }
//    }
//
//    // here check for the squares where the selected square may move to
//    if (selectedSquare && selectedSquare->chessPiece) {
//
//        std::vector<Move *> availableMoves;
//        availableMoves = selectedSquare->chessPiece->getAvailableMoves(true);
//
//        for (Move * move : availableMoves) {
//            move->endOfMove->setFocused(true);
//        }
//    }
//}