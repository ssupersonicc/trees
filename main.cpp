#include <SFML/Graphics.hpp>

#include "header.hpp"
// класс прокрутки
// изменение масштаба

extern int type;

int main() {
  sf::RenderWindow window(sf::VideoMode(1280, 960), "Trees");
  Interface();
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      CheckButtons(event, window);
    }
    window.clear(sf::Color::White);
    DrawInterface(window);
    //DrawTree(type, window);
    window.display();
  }
}