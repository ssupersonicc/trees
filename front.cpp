#include <string>
#include <cmath>

#include "header.hpp"

int type = 0;
int scale = 1;

// ----------------------------BUTTON------------------------------

void Button::setSize(double height_, double width_) {
  height = height_;
  width = width_;
  return;
}

void Button::setText(std::string text_, sf::Color color_ = sf::Color::Black) {
  text.setText(text_);
  text.setColor(color_);
  text.setPositionRec(x, y, height, width);
  return;
}

void Button::setPosition(double x_, double y_) {
  x = x_;
  y = y_;
  return;
}

void Button::setColor(sf::Color color_ = sf::Color(169, 169, 169)) {
  color = color_;
  return;
}

bool Button::isClicked(sf::Event event) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      double mouse_x = event.mouseButton.x;
      double mouse_y = event.mouseButton.y;
      if (mouse_x >= x && mouse_x <= x + width && mouse_y >= y &&
          mouse_y <= y + height) {
        return true;
      }
    }
  }
  return false;
}

void Button::draw(sf::RenderWindow &window) {
  sf::RectangleShape button;
  button.move(x, y);
  button.setFillColor(color);
  button.setSize(sf::Vector2f(width, height));
  window.draw(button);

  text.draw(window, 18);
  return;
}

//------------------------------TEXT-----------------------------
int Text::length() { return text.length(); }

void Text::setText(std::string text_) {
  text = text_;
  return;
}

void Text::setColor(sf::Color color_ = sf::Color::Black) {
  color = color_;
  return;
}

void Text::setPositionRec(double x_, double y_, double height, double width) {
  x = x_ + (width - text.length() * 11) / 2.0;
  y = y_ + (height - 18) / 2.0;
  return;
}

void Text::setPositionCir(double x_, double y_, double r, double h, int call) {
  if (call == 1) {
    x = x_ + 2;
    y = y + (r * 2 - h) / 2.0;
  } else if (call == 2) {
    x = x_ + r / 2.0 + 2;
    y = y_ - r / 2.0;
  } else if (call == 3) {
    x = x + r / 2.0 + 2;
    y = y + r / 2.0;
  }
  return;
}

void Text::draw(sf::RenderWindow &window, int size) {
  sf::Font font;
  if (font.loadFromFile("DroidSansMono.ttf")) {
    sf::Text txt;
    txt.setFont(font);
    txt.setString(text);
    txt.setCharacterSize(size);
    txt.setFillColor(color);
    txt.move(x, y);
    window.draw(txt);
  }
  return;
}

//----------------------------NODE----------------------------

void Node::setColor(sf::Color color_) {
  color = color_;
  return;
}

void Node::setPosition(double x_, double y_) {
  x = x_;
  y = y_;
  return;
}

void Node::setValue() {
  num.setText(std::to_string(nd.num));
  num.setColor(sf::Color::Black);
  if (nd.wt != -1) {
    wt.setText(std::to_string(nd.wt));
    wt.setColor(sf::Color::Black);
  } else {
  }
  return;
}

bool Node::isClicked(sf::Event event) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      double mouse_x = event.mouseButton.x;
      double mouse_y = event.mouseButton.y;
      if ((mouse_x - x) * (mouse_x - x) + (-mouse_y + y) * (-mouse_y + y) <=
          r * r)
        return true;
      else
        return false;
    }
  }
  return false;
}

void Node::draw(sf::RenderWindow &window) {
  sf::CircleShape shape(r);
  shape.setFillColor(color);
  shape.move(x, y);
  window.draw(shape);

  double d;
  const double coef = 1.61803398875;
  if (nd.wt != -1) {
    d = r;

    double len_num = (d - 4) / num.length();
    int size_num = len_num * coef;
    num.setPositionCir(x, y, r, size_num, 2);
    num.draw(window, size_num);

    double len_wt = (d - 4) / wt.length();
    int size_wt = len_wt * coef;
    wt.setPositionCir(x, y, r, size_wt, 3);
    wt.draw(window, size_wt);
  } else {
    d = r * 2;
    double len = (d - 4) / num.length();
    int size = len * coef;
    num.setPositionCir(x, y, r, size, 1);
    num.draw(window, size);
  }
  return;
}

//-------------------------INTERFACE--------------------------
Button but_info;
Button but_avl;
Button but_rbt;
Button but_treap;
Button but_splay;
Button but_sett;

Button but_add;
Button but_addrand;
Button but_plus;
Button but_minus;

void Interface() {
  but_info.setSize(30, 100);
  but_info.setColor();
  but_info.setPosition(10, 10);
  but_info.setText("info");

  but_avl.setSize(30, 100);
  but_avl.setColor();
  but_avl.setPosition(115, 10);
  but_avl.setText("AVL");

  but_rbt.setSize(30, 100);
  but_rbt.setColor();
  but_rbt.setPosition(220, 10);
  but_rbt.setText("RB-tree");

  but_treap.setSize(30, 100);
  but_treap.setPosition(325, 10);
  but_treap.setColor();
  but_treap.setText("treap");

  but_splay.setSize(30, 100);
  but_splay.setPosition(430, 10);
  but_splay.setColor();
  but_splay.setText("splay");

  but_sett.setSize(30, 100);
  but_sett.setColor();
  but_sett.setPosition(535, 10);
  but_sett.setText("settings");

  but_add.setSize(50, 200);
  but_add.setColor();
  but_add.setPosition(10, 880);
  but_add.setText("ADD");

  but_addrand.setSize(50, 200);
  but_addrand.setColor();
  but_addrand.setPosition(220, 880);
  but_addrand.setText("ADD RANDOM");

  but_plus.setSize(50, 50);
  but_plus.setColor();
  but_plus.setPosition(430, 880);
  but_plus.setText("+");

  but_minus.setSize(50, 50);
  but_minus.setColor();
  but_minus.setPosition(485, 880);
  but_minus.setText("-");

  return;
}

void DrawInterface(sf::RenderWindow &window) {
  but_info.draw(window);
  but_avl.draw(window);
  but_rbt.draw(window);
  but_treap.draw(window);
  but_splay.draw(window);
  but_sett.draw(window);
  if (type != 0 && type != 5) {
    but_add.draw(window);
    but_addrand.draw(window);
    but_plus.draw(window);
    but_minus.draw(window);
  }
  return;
}

void CheckButtons(sf::Event event, sf::RenderWindow &window) {
  if (but_info.isClicked(event)) {
    Info(window);
    type = 0;
    but_info.setColor(sf::Color(176, 196, 222));
    but_avl.setColor();
    but_rbt.setColor();
    but_treap.setColor();
    but_splay.setColor();
    but_sett.setColor();
  }
  if (but_avl.isClicked(event)) {
    type = 1;
    but_info.setColor();
    but_avl.setColor(sf::Color(176, 196, 222));
    but_rbt.setColor();
    but_treap.setColor();
    but_splay.setColor();
    but_sett.setColor();
  }
  if (but_rbt.isClicked(event)) {
    type = 2;
    but_info.setColor();
    but_avl.setColor();
    but_rbt.setColor(sf::Color(176, 196, 222));
    but_treap.setColor();
    but_splay.setColor();
    but_sett.setColor();
  }
  if (but_treap.isClicked(event)) {
    type = 3;
    but_info.setColor();
    but_avl.setColor();
    but_rbt.setColor();
    but_treap.setColor(sf::Color(176, 196, 222));
    but_splay.setColor();
    but_sett.setColor();
  }
  if (but_splay.isClicked(event)) {
    type = 4;
    but_info.setColor();
    but_avl.setColor();
    but_rbt.setColor();
    but_treap.setColor();
    but_splay.setColor(sf::Color(176, 196, 222));
    but_sett.setColor();
  }
  if (but_sett.isClicked(event)) {
    type = 5;
    Settings(window);
    but_info.setColor();
    but_avl.setColor();
    but_rbt.setColor();
    but_treap.setColor();
    but_splay.setColor();
    but_sett.setColor(sf::Color(176, 196, 222));
  }
  if (but_add.isClicked(event)) {
    long long num = getNum(window);
    Add(num);
  }
  if (but_addrand.isClicked(event)) {
  }
  if (but_plus.isClicked(event)) {
  }
  if (but_minus.isClicked(event)) {
  }
  return;
}

long long getNum(sf::RenderWindow &window) {
  std::string str;
  while (true) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter && str.length() != 0) {
          but_add.setColor();
          but_add.setText("ADD");
          return std::stoll(str);
        }
      }
      if (event.type == sf::Event::TextEntered && event.text.unicode != 8 &&
          event.text.unicode != 13 && event.text.unicode >= '0' &&
          event.text.unicode <= '9') {
        str += static_cast<char>(event.text.unicode);
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::BackSpace && str.length() > 0) {
          str.erase(str.length() - 1);
        }
      }
    }
    but_add.setColor(sf::Color(176, 196, 222));
    but_add.setText(str);
    window.clear(sf::Color::White);
    DrawInterface(window);
    window.display();
  }
}

void Info(sf::RenderWindow &window) { return; }

void Settings(sf::RenderWindow &window) { return; }

extern Node *avl;
extern Node *rb;
extern Node *splay;
extern Node *treap;

void DrawTree(int type, sf::RenderWindow &window) {
  Node *T = nullptr;
  if (type == 1)
    T = avl;
  else if (type == 2)
    T = rb;
  else if (type == 3)
    T = splay;
  else if (type == 4)
    T = treap;

  int H = h(T);
  int r = scale * 10;
  int count = std::pow(2, H - 1);
  double dist = r / 2.0;
  
  return;
}