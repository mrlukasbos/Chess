#include <SFML/Graphics.hpp>
#include "Board.h"
#include "HumanPlayer.h"

using namespace sf;

int main() {

    // set the context
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Chess", Style::Default, settings);

    // draw the board & init game
    Board board(window);
    Player *bottomPlayer = new HumanPlayer(WHITE);
    Player *topPlayer = new HumanPlayer(BLACK);
    board.startGame(bottomPlayer, topPlayer);

    //start interface
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            Color menuColor(220, 220, 220); // light gray
            window.clear(menuColor);

            board.drawBoard(); // this is where the redraw of the board happens



            if (sf::Keyboard::isKeyPressed(Keyboard::B)) {
                Player *bottomPlayer = new HumanPlayer(WHITE);
                Player *topPlayer = new HumanPlayer(BLACK);
                board.startGame(bottomPlayer, topPlayer);

            } else if (Keyboard::isKeyPressed(Keyboard::W)) {
                Player *bottomPlayer = new HumanPlayer(BLACK);
                Player *topPlayer = new HumanPlayer(WHITE);
                board.startGame(bottomPlayer, topPlayer);
            }

            Font font;
            Font boldFont;
            font.loadFromFile("OpenSans-Regular.ttf");
            boldFont.loadFromFile("OpenSans-Bold.ttf");

            GridElement *selectedElement = board.selectedGridElement;
            if (selectedElement) {
                Vector2i newCoordinates = selectedElement->coordinates;
                board.selectGridElementFromCoordinates(newCoordinates);

                Text elementName(selectedElement->name, font, 26);
                elementName.setFillColor(Color::Black);
                elementName.setCharacterSize(32);
                elementName.setPosition(BOARD_SIZE + 40, 120);

                window.draw(elementName);
            }

            Text currentMoveText("Current move", font, 26);
            currentMoveText.setFillColor(Color::Black);
            currentMoveText.setCharacterSize(24);
            currentMoveText.setPosition(BOARD_SIZE + 40, 20);

            Text currentColorToMoveName(board.currentPlayer->color == BLACK ? "Black" : "White", boldFont, 26);
            currentColorToMoveName.setFillColor(Color::Black);
            currentColorToMoveName.setCharacterSize(48);
            currentColorToMoveName.setPosition(BOARD_SIZE + 40, 40);

            window.draw(currentMoveText);
            window.draw(currentColorToMoveName);
            window.display();
        }
    }
    return 0;
}
