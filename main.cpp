#include <SFML/Graphics.hpp>
#include "GridElement.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800,800),"Chess");

    sf::Font font;
    font.loadFromFile("OpenSans-Bold.ttf");
    sf::Text text("Chess", font, 11);
    text.setCharacterSize(32);
    text.setPosition(window.getSize().x/2 - text.getGlobalBounds().width/2,
                     window.getSize().y/2 - text.getGlobalBounds().height/2);

    const short BLOCK_SIZE = 100;

    // initialize all grid elements
    GridElement elements[8][8];
    for (short i  = 0; i < 8; i++) {
        for (short j = 0; j < 8; j++) {
            sf::Color color = (j+i)%2 == 1 ? sf::Color::Black : sf::Color::White;
            elements[i][j] = GridElement(i * BLOCK_SIZE, j*BLOCK_SIZE, BLOCK_SIZE, color);
        }
    }

    //start interface
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }
            window.clear(sf::Color::Black);
            window.draw(text);

            //draw the gridElements
            for (short i  = 0; i < 8; i++) {
                for (short j = 0; j < 8; j++) {
                    window.draw(elements[i][j].rectangle);
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                printf("mouse clicked at location: %d, %d", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            }

            window.display();
        }
    }
    return 0;
}

