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
    currentMoveText.setPosition(BOARD_SIZE + 40, WINDOW_HEIGHT / 2 - 50);

    Text currentColorToMoveName(currentPlayer->color == BLACK ? "Black" : "White", boldFont, 26);
    currentColorToMoveName.setFillColor(Color::Black);
    currentColorToMoveName.setCharacterSize(48);
    currentColorToMoveName.setPosition(BOARD_SIZE + 40, WINDOW_HEIGHT / 2 - 20);

    window.draw(currentMoveText);
    window.draw(currentColorToMoveName);
}

void Interface::showSelectedGridElementName() {

    GridElement *selectedElement = board.selectedGridElement;
    if (selectedElement) {
        Vector2i newCoordinates = selectedElement->coordinates;
        board.selectGridElementFromCoordinates(newCoordinates);

        Text elementName(selectedElement->name, font, 26);
        elementName.setFillColor(Color::Black);
        elementName.setCharacterSize(32);
        elementName.setPosition(BOARD_SIZE + 40, WINDOW_HEIGHT / 2 + 40);

        window.draw(elementName);
    }
}

void Interface::showPlayerTypes() {
    Text topPlayerTypeText(board.topPlayer->getType(), font, 26);
    topPlayerTypeText.setFillColor(Color::Black);
    topPlayerTypeText.setCharacterSize(24);
    topPlayerTypeText.setPosition(BOARD_SIZE + 40, 40);

    Text bottomPlayerTypeText(board.bottomPlayer->getType(), font, 26);
    bottomPlayerTypeText.setFillColor(Color::Black);
    bottomPlayerTypeText.setCharacterSize(24);
    bottomPlayerTypeText.setPosition(BOARD_SIZE + 40, WINDOW_HEIGHT - 80);

    window.draw(topPlayerTypeText);
    window.draw(bottomPlayerTypeText);
};



