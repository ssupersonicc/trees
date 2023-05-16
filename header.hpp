#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Scrolling {
 private:
  double x, y;
  sf::Color color;
  double height, width;

 public:
  void setColor(sf::Color color_);
  void setPosition(double x_, double y_);
  void isMoved(sf::Event event);
  bool isClicked(sf::Event event);
  void setSize(double height_, double width_);
  void draw(sf::RenderWindow &widnow);
};

class Text {
 private:
  double x, y;
  std::string text;
  sf::Color color;
  int size;

 public:
  void setText(std::string text_);
  void setColor(sf::Color color_);
  void setSize(int size_);
  void setPositionRec(double x_, double y_, double height, double width);
  void setPositionCir(double x_, double y_, double dx, double dy);
  void draw(sf::RenderWindow &window, double dx, double dy);
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
  void setValue(double x, double y, double r);
  bool isClicked(sf::Event event);
  void draw(sf::RenderWindow &window);
  std::pair<double, double> getPosition();
  Node *left, *right, *parent;
  node nd;
  double r;
  int pos;

 private:
  double x, y;
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

//-----------front------------
void Interface();
void DrawInterface(sf::RenderWindow &window);
void CheckButtons(sf::Event event, sf::RenderWindow &window);
void CheckNode(sf::Event event, sf::RenderWindow &window);
bool CheckTree(Node *&t, sf::Event event);
void Info(sf::RenderWindow &window);
void Settings(sf::RenderWindow &window);

long long getNum(sf::RenderWindow &window);
long long getCount(sf::RenderWindow &window);
void DrawTree(sf::RenderWindow &window);
void Update(Node *&t, int dy, int pos,
            std::vector<std::pair<double, double>> &coord);
void Restructuring(int type);
void Draw(Node *t, sf::RenderWindow &window);

void setSizePos(double x, double y, double d, std::string str, Text &text);

//-----------back-------------
bool addAVL(Node *&T, long long num);
void Add(long long num, sf::RenderWindow &window);
Node *insert(Node *&T, Node *&prev, long long num);
Node* delete_elem(Node *&t);
void del_avl(Node*&t);

int h(Node *t);
void LeftRotate(Node *&t);
void RightRotate(Node *&t);
void BitLeftRotate(Node *&t);
void BigRightRotate(Node *&t);

int HReverse(Node *t);
