#include <SFML/Graphics.hpp>
#include "Board.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800,800),"Chess");

    sf::Font font;
    font.loadFromFile("OpenSans-Bold.ttf");
    sf::Text text("Chess", font, 11);
    text.setCharacterSize(32);
    text.setPosition(window.getSize().x/2 - text.getGlobalBounds().width/2,
                     window.getSize().y/2 - text.getGlobalBounds().height/2);

    Board board;

    //start interface
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }
            window.clear(sf::Color::Black);
            window.draw(text);

            board.drawBoard(window);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                printf("mouse clicked at location: %d, %d", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            }

            window.display();
        }
    }
    return 0;
}

