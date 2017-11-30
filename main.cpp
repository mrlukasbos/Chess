
#include <SFML/Graphics.hpp>
#include "GridElement.h"


int main() {

    sf::RenderWindow window(sf::VideoMode(800,800,32),"Hello SFML");

    sf::Font font;
    font.loadFromFile("OpenSans-Bold.ttf");

    sf::Text text("Chess", font, 11);
    text.setCharacterSize(32);
    text.setPosition(window.getSize().x/2 - text.getGlobalBounds().width/2,
                     window.getSize().y/2 - text.getGlobalBounds().height/2);

    GridElement element(10, 10, 100);

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }
            window.clear(sf::Color::Black);
            window.draw(text);
            window.draw(element.rectangle);
            window.display();
        }
    }
    return 0;
}