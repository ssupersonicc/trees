#include <SFML/Graphics.hpp>
#include "back.hpp"
#include "front.hpp"

//подсветка выбора текущего окна 

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Trees");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear(sf::Color::White);
        Interface(window);
        window.display();
    }
}
