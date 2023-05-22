#include <SFML/Graphics.hpp>

#include "header.hpp"
// скролл по y

// цвета

extern int type;

int main() {
  sf::RenderWindow window(sf::VideoMode(1280, 960), "Trees");
  Interface();
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      CheckButtons(event, window);
      CheckNode(event, window);
    }
    window.clear(sf::Color::White);
    DrawTree(window);
    DrawInterface(window);
    window.display();
  }
}