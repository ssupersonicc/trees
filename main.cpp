#include <SFML/Graphics.hpp>

#include "header.hpp"
// расположение числа
// размер линии между узлами

// вычислить значение коэффициента для скролла

// как-то тупо рисует если удалять всегда верхний элемент
// проверить является ли t->left поддеревом t->parent (в удалении)

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