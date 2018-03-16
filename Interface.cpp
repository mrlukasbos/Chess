//
// Created by Lukas Bos on 19/02/2018.
//

#include "Interface.h"


Interface::Interface(RenderWindow &window, Board &board)
        : window(window), board(board), currentPlayer(currentPlayer) {

    font.loadFromFile("OpenSans-Regular.ttf");
    boldFont.loadFromFile("OpenSans-Bold.ttf");
}

void Interface::showCurrentPlayerText(Player *currentPlayer) {
    Text currentMoveText("Current move", font, 26);
    currentMoveText.setFillColor(Color::Black);
    currentMoveText.setCharacterSize(24);
    currentMoveText.setPosition(GAME_SIZE + 40, WINDOW_HEIGHT / 2 - 50);

    Text currentColorToMoveName(currentPlayer->color == BLACK ? "Black" : "White", boldFont, 26);
    currentColorToMoveName.setFillColor(Color::Black);
    currentColorToMoveName.setCharacterSize(48);
    currentColorToMoveName.setPosition(GAME_SIZE + 40, WINDOW_HEIGHT / 2 - 20);

    window.draw(currentMoveText);
    window.draw(currentColorToMoveName);
}

void Interface::showSelectedSquareName() {

    Square *selectedElement = board.selectedSquare;
    if (selectedElement) {
        Vector2i newCoordinates = selectedElement->coordinates;
        board.selectSquareFromCoordinates(newCoordinates);

        Text squareName(selectedElement->name, font, 26);
        squareName.setFillColor(Color::Black);
        squareName.setCharacterSize(32);
        squareName.setPosition(GAME_SIZE + 40, WINDOW_HEIGHT / 2 + 40);

        window.draw(squareName);
    }
}

void Interface::showPlayerTypes() {
    Text topPlayerTypeText(board.topPlayer->getType(), font, 26);
    topPlayerTypeText.setFillColor(Color::Black);
    topPlayerTypeText.setCharacterSize(24);
    topPlayerTypeText.setPosition(GAME_SIZE + 40, 40);

    Text bottomPlayerTypeText(board.bottomPlayer->getType(), font, 26);
    bottomPlayerTypeText.setFillColor(Color::Black);
    bottomPlayerTypeText.setCharacterSize(24);
    bottomPlayerTypeText.setPosition(GAME_SIZE + 40, WINDOW_HEIGHT - 80);

    window.draw(topPlayerTypeText);
    window.draw(bottomPlayerTypeText);
};

void Interface::showBoardBackground() {
//    sf::Image img;
//    img.loadFromFile("images/darkwood.jpg");
//    sf::Texture texture;
//    texture.loadFromImage(img);
//
//    const sf::Texture *pTexture = &texture;

    sf::RectangleShape boardBackground;
    boardBackground.setPosition(10, 10);

    boardBackground.setSize(sf::Vector2f(GAME_SIZE -20, GAME_SIZE -20));
  //  boardBackground.setTexture(pTexture);

    boardBackground.setFillColor(Color::Black);
    window.draw(boardBackground);
}

void Interface::showCoordinates() {
    char letters[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    for (short i = 0; i<8; i++) {
        Text coordinateNumberPart(std::to_string(8-i), boldFont, 18);
        Text coordinateLetterPart(letters[i], boldFont, 18);

        coordinateLetterPart.setFillColor(Color::White);
        coordinateLetterPart.setCharacterSize(20);
        coordinateLetterPart.setPosition(BOARD_BORDER_THICKNESS + 40 + (i * BLOCK_SIZE), GAME_SIZE - 40);

        coordinateNumberPart.setFillColor(Color::White);
        coordinateNumberPart.setCharacterSize(20);
        coordinateNumberPart.setPosition(15, BOARD_BORDER_THICKNESS + 40 + (i * BLOCK_SIZE));

        window.draw(coordinateLetterPart);
        window.draw(coordinateNumberPart);
    }
}


