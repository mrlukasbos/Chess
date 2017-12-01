#include <SFML/Graphics.hpp>
#include "Board.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800,800),"Chess");

    Board board(window);
    board.startGame();

    //start interface
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }

            window.clear(sf::Color::Black);

            board.drawBoard();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                board.selectGridElement( sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            }

            window.display();
        }
    }
    return 0;
}

