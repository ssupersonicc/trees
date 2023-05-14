#pragma once
#include <SFML/Graphics.hpp>
#include <string>

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
  struct node {
    bool color;  // false
    long long num;
    long long wt;
  };
  void setPosition(double x_, double y_);
  void setColor(sf::Color color_);
  void setValue();
  bool isClicked(sf::Event event);
  void draw(sf::RenderWindow &window);
  Node *left, *right, *parent;
  node nd;

 private:
  double x, y;
  double r;
  sf::Color color;
  Text num;
  Text wt;
};

class Button {
 private:
  double x, y;
  double height, width;
  Text text;
  sf::Color color;

 public:
  void setSize(double height_, double width_);
  void setText(std::string text_, sf::Color color_);
  void setPosition(double x_, double y_);
  void setColor(sf::Color color_);
  bool isClicked(sf::Event event);
  void draw(sf::RenderWindow &window);
};

void Interface();
void DrawInterface(sf::RenderWindow &window);
void CheckButtons(sf::Event event, sf::RenderWindow &window);
void Info(sf::RenderWindow &window);
void Settings(sf::RenderWindow &window);

long long getNum(sf::RenderWindow &window);

void addAVL(Node *&T, long long num);
void Add(long long num);
Node *insert(Node *&T, Node *&prev, long long num);

int h(Node *t);
void LeftRotate(Node *&t);
void RightRotate(Node *&t);
void BitLeftRotate(Node *&t);
void BigRightRotate(Node *&t);

void DrawTree(int type, sf::RenderWindow &window);
