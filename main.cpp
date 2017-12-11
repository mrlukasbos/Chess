#include <SFML/Graphics.hpp>
#include "Board.h"

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32),"Chess",sf::Style::Default, settings);

    Board board(window);
    board.startGame(WHITE, BLACK);

    //start interface
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }
            sf::Color menuColor(220, 220, 220);
            window.clear(menuColor);

            board.drawBoard();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                board.selectGridElementFromMousePos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
                board.startGame(BLACK, WHITE);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                board.startGame(WHITE, BLACK);
            }


            sf::Font font;
            font.loadFromFile("OpenSans-Regular.ttf");

            sf::Font boldFont;
            boldFont.loadFromFile("OpenSans-Bold.ttf");

            GridElement *selectedElement = board.selectedGridElement;
            if (selectedElement) {

                sf::Vector2i newCoordinates = selectedElement->coordinates;
                board.selectGridElementFromCoordinates(newCoordinates);

                sf::Text elementName(selectedElement->name, font, 26);
                elementName.setFillColor(sf::Color::Black);
                elementName.setCharacterSize(32);
                elementName.setPosition(BOARD_SIZE + 40, 120);

                window.draw(elementName);
            }

            sf::Text currentMoveText("Current move", font, 26);
            currentMoveText.setFillColor(sf::Color::Black);
            currentMoveText.setCharacterSize(24);
            currentMoveText.setPosition(BOARD_SIZE + 40, 20);

            sf::Text currentColorToMoveName(board.currentPlayer->color == BLACK ? "Black" : "White", boldFont, 26);
            currentColorToMoveName.setFillColor(sf::Color::Black);
            currentColorToMoveName.setCharacterSize(48);
            currentColorToMoveName.setPosition(BOARD_SIZE + 40, 40);

            window.draw(currentMoveText);
            window.draw(currentColorToMoveName);
            window.display();
        }
    }
    return 0;
}

