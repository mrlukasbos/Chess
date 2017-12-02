#include <SFML/Graphics.hpp>
#include "Board.h"
#include "constants.h"

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32),"Chess",sf::Style::Default, settings);

    Board board(window);
    board.startGame();

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


            GridElement *selectedElement = board.selectedGridElement;
            if (selectedElement) {

                sf::Vector2i newCoordinates = selectedElement->coordinates;

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    newCoordinates.x = (newCoordinates.x + 7) % 8;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    newCoordinates.x = (newCoordinates.x + 1) % 8;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    newCoordinates.y = (newCoordinates.y + 7) % 8;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    newCoordinates.y = (newCoordinates.y + 1) % 8;
                }

                board.selectGridElementFromCoordinates(newCoordinates);


                sf::Font font;
                font.loadFromFile("OpenSans-Bold.ttf");


                sf::Text text(selectedElement->name, font, 26);
                text.setFillColor(sf::Color::Black);
                text.setCharacterSize(32);
                text.setPosition(BOARD_SIZE + 40, 40);

                window.draw(text);
            }


            window.display();
        }
    }
    return 0;
}

