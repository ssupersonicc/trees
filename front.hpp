#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "back.hpp"

class Text {
 private:
  double x, y;
  std::string text;
  sf::Color color;

 public:
  void setText(std::string text_);
  void setColor(sf::Color color_);
  void setPositionRec(double x_, double y_, double height, double width);
  void setPositionCir(double x_, double y_, double r, double h, int call);
  void draw(sf::RenderWindow &window, int size);
  int length();
};

class Node {
 public:
  struct node;
  void setPosition(double x_, double y_);
  void setColor(sf::Color color_);
  void setValue();
  bool isClicked(sf::Event event);
  void draw(sf::RenderWindow &window);
  Node *left, *right, *parent;

 private:
  double x, y;
  double r;
  sf::Color color;
  node *nd;
  Text num;
  Text wt;
};

struct Node::node {
  bool color;  // false
  long long num;
  long long wt;
};

class Button {
 private:
  double x, y;
  double height, width;
  Text text;
  sf::Color color;

 public:
  void setSize(double height_, double width_);
  void setText(std::string text_, sf::Color color_ = sf::Color::Black);
  void setPosition(double x_, double y_);
  void setColor(sf::Color color_ = sf::Color(169, 169, 169));
  bool isClicked(sf::Event event);
  void draw(sf::RenderWindow &window);
};

void Interface(sf::RenderWindow &window);