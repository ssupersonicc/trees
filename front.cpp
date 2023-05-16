#include <cmath>
#include <ctime>
#include <string>

#include "header.hpp"
#define PI 3.14159265

int type = 0;
int scale = 2;

double scroll_x = 0, scroll_y = 0;
double scroll_coef_x = 1;
double scroll_coef_y = 1;

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

  text.setSize(18);
  text.draw(window, 0, 0);
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

void Text::setPositionCir(double x_, double y_, double dx, double dy) {
  x = x_ + dx;
  y = y_ + dy;
  return;
}

void Text::draw(sf::RenderWindow &window, double dx, double dy) {
  sf::Font font;
  if (font.loadFromFile("DroidSansMono.ttf")) {
    sf::Text txt;
    txt.setFont(font);
    txt.setString(text);
    txt.setCharacterSize(size);
    txt.setFillColor(color);
    txt.setPosition(x + dx, y + dy);
    window.draw(txt);
  }
  return;
}

void Text::setSize(int size_) {
  size = size_;
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

void setSizePos(double x, double y, double d, std::string str, Text &text) {
  const double coef = 1.61803398875;
  text.setText(str);
  text.setColor(sf::Color::Black);
  int size = d - 4;
  int len = size / coef;
  if (len * str.length() > d - 4) {
    len = (d - 4) / str.length();
    size = len * coef;
    text.setPositionCir(x, y, 2, (d - size) / 2.0);
  } else {
    text.setPositionCir(x, y, (d - len * str.length()) / 2.0, 2);
  }
  text.setSize(size);
  return;
}

void Node::setValue(double x, double y, double r) {
  std::string num_str = std::to_string(nd.num);
  num.setText(num_str);
  num.setColor(sf::Color::Black);
  if (nd.wt != -1) {
    std::string wt_str = std::to_string(nd.wt);
    setSizePos(x, y, r, num_str, num);
    setSizePos(x + r, y, r, wt_str, wt);
  } else {
    setSizePos(x, y, r * 2, num_str, num);
  }
  return;
}

bool Node::isClicked(sf::Event event) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      double mouse_x = event.mouseButton.x - scroll_x * scroll_coef_x;
      double mouse_y = event.mouseButton.y - scroll_y * scroll_coef_y;
      double a = x + r;
      double b = y + r;
      if ((mouse_x - a) * (mouse_x - a) + (-mouse_y + b) * (-mouse_y + b) <=
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
  shape.move(x + scroll_x * scroll_coef_x, y + scroll_y * scroll_coef_y);
  window.draw(shape);

  num.draw(window, scroll_x * scroll_coef_x, scroll_y * scroll_coef_y);
  if (nd.wt != -1)
    wt.draw(window, scroll_x * scroll_coef_x, scroll_y * scroll_coef_y);
  return;
}

std::pair<double, double> Node::getPosition() { return {x, y}; }

//-------------------------SCROLLING---------------------------

void Scrolling::setColor(sf::Color color_) {
  color = color_;
  return;
}

void Scrolling::setPosition(double x_, double y_) {
  x = x_;
  y = y_;
  return;
}

void Scrolling::setSize(double height_, double width_) {
  height = height_;
  width = width_;
  return;
}

void Scrolling::isMoved(sf::Event event) {
  if (event.type == sf::Event::MouseMoved) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      double mouse_x = event.mouseMove.x;
      double mouse_y = event.mouseMove.y;
      if (width > height) {
        double new_x = mouse_x - width / 2.0;
        if (new_x < 0) new_x = 0;
        if (new_x + width > 1280) new_x = 1280 - width;
        x = new_x;
        scroll_x = new_x - 610;
        return;
      } else {
        double new_y = mouse_y - height / 2.0;
        if (new_y < 0) new_y = 0;
        if (new_y + height > 960) new_y = 960 - height;
        y = new_y;
        scroll_y = y;
        return;
      }
    }
  }
  return;
}

void Scrolling::draw(sf::RenderWindow &window) {
  if (width > height) {
    sf::RectangleShape line;
    line.setSize(sf::Vector2f(1280, 3));
    line.setFillColor(sf::Color(128, 128, 128));
    line.setPosition(0, 943);
    window.draw(line);
  } else {
    sf::RectangleShape line;
    line.setSize(sf::Vector2f(3, 960));
    line.setFillColor(sf::Color(128, 128, 128));
    line.setPosition(1263, 0);
    window.draw(line);
  }
  sf::RectangleShape scr;
  scr.setSize(sf::Vector2f(width, height));
  scr.setFillColor(color);
  scr.setPosition(x, y);
  window.draw(scr);
  return;
}

bool Scrolling::isClicked(sf::Event event) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    double mouse_x = event.mouseButton.x;
    double mouse_y = event.mouseButton.y;
    if (mouse_x >= x && mouse_x <= x + width && mouse_y >= y &&
        mouse_y <= y + height) {
      return true;
    }
  }
  return false;
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

Scrolling updown;
Scrolling rightleft;
extern Node *avl, *rb, *splay, *treap;
Button field1, field2, field3;

void Interface() {
  field1.setSize(50, 1280);
  field1.setPosition(0, 0);
  field1.setColor(sf::Color::White);

  field2.setSize(90, 1280);
  field2.setPosition(0, 870);
  field2.setColor(sf::Color::White);

  field3.setSize(960, 30);
  field3.setPosition(1250, 0);
  field3.setColor(sf::Color::White);

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

  updown.setSize(20, 60);
  updown.setColor(sf::Color(70, 130, 180));
  updown.setPosition(610, 933);

  rightleft.setSize(60, 20);
  rightleft.setColor(sf::Color(70, 130, 180));
  rightleft.setPosition(1253, 0);

  return;
}

void DrawInterface(sf::RenderWindow &window) {
  field1.draw(window);
  field2.draw(window);
  field3.draw(window);

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
  updown.draw(window);
  rightleft.draw(window);
  return;
}

bool scroll_xf, scroll_yf;
void CheckButtons(sf::Event event, sf::RenderWindow &window) {
  srand(time(NULL));
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
    Add(num, window);
  }
  if (but_addrand.isClicked(event)) {
    long long n = getCount(window);
    for (int i = 0; i < n; ++i) {
      int num = rand() % 100;
      Add(num, window);
    }
  }
  if (but_plus.isClicked(event)) {
    ++scale;
    Restructuring(type);
  }
  if (but_minus.isClicked(event)) {
    --scale;
    if (scale <= 0) scale = 1;
    Restructuring(type);
  }

  if (scroll_yf) {
    updown.isMoved(event);
  }
  if (scroll_xf) {
    rightleft.isMoved(event);
  }
  if (updown.isClicked(event)) {
    scroll_yf = true;
  }
  if (rightleft.isClicked(event)) {
    scroll_xf = true;
  }

  if (event.type == sf::Event::MouseButtonReleased) {
    scroll_xf = false;
    scroll_yf = false;
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
    DrawTree(window);
    window.display();
  }
}

long long getCount(sf::RenderWindow &window) {
  std::string str;
  while (true) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter && str.length() != 0) {
          but_addrand.setColor();
          but_addrand.setText("ADD RANDOM");
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
    but_addrand.setColor(sf::Color(176, 196, 222));
    but_addrand.setText(str);
    window.clear(sf::Color::White);
    DrawInterface(window);
    DrawTree(window);
    window.display();
  }
}

void Info(sf::RenderWindow &window) { return; }

void Settings(sf::RenderWindow &window) { return; }

void Update(Node *&t, int dy, int pos,
            std::vector<std::pair<double, double>> &coord) {
  int r = 10 * scale;
  if (t == nullptr) return;
  t->setColor(sf::Color(50, 205, 50));
  t->r = r;
  t->pos = pos;
  int h_rev = HReverse(t);
  --h_rev;
  t->setPosition(coord[h_rev].first + (2 * r + coord[h_rev].second) * (pos - 1),
                 dy);
  dy += 3 * t->r;
  std::pair<double, double> p = t->getPosition();
  t->setValue(p.first, p.second, r);
  Update(t->left, dy, pos * 2 - 1, coord);
  Update(t->right, dy, pos * 2, coord);
  return;
}

void DrawTree(sf::RenderWindow &window) {
  Node *t = nullptr;
  if (type == 1) {
    t = avl;
  }
  Draw(t, window);
  return;
}

void Draw(Node *t, sf::RenderWindow &window) {
  if (t == nullptr) return;
  std::pair<double, double> p = t->getPosition();
  if (t->right != nullptr) {
    double dx = 0, dy = 0;
    sf::RectangleShape line;
    double angle = 0;
    std::pair<double, double> p1 = t->right->getPosition();
    dx = p1.first - p.first;
    dy = p1.second - p.second;
    angle = atan2(dy, dx) * 180 / PI;
    double len = sqrt(dx * dx + dy * dy);
    line.move(p.first + t->r + scroll_x * scroll_coef_x,
              p.second + t->r + scroll_y * scroll_coef_y);
    line.setSize(sf::Vector2f(len, 3.0));
    line.setFillColor(sf::Color(105, 105, 105));
    line.rotate(angle);
    window.draw(line);
  }
  if (t->left != nullptr) {
    double dx = 0, dy = 0;
    sf::RectangleShape line;
    double angle = 0;
    std::pair<double, double> p1 = t->left->getPosition();
    dx = p.first - p1.first;
    dy = p1.second - p.second;
    angle = atan2(dy, dx) * 180 / PI;
    angle = 180 - angle;
    double len = sqrt(dx * dx + dy * dy);
    line.move(p.first + t->r + scroll_x * scroll_coef_x,
              p.second + t->r + scroll_y * scroll_coef_y);
    line.setSize(sf::Vector2f(len, 3.0));
    line.setFillColor(sf::Color(105, 105, 105));
    line.rotate(angle);
    window.draw(line);
  }
  t->draw(window);
  Draw(t->right, window);
  Draw(t->left, window);
  return;
}

void CheckNode(sf::Event event, sf::RenderWindow &window) {
  if (event.type == sf::Event::MouseButtonPressed) {
    bool f = false;
    if (type == 1) {
      f = CheckTree(avl, event);
    }
    if (f) {
      Restructuring(type);
    }
  }
  return;
}

bool CheckTree(Node *&t, sf::Event event) {
  if (t == nullptr) return false;
  if (t->isClicked(event)) {
    del_avl(t);
    return true;
  }
  return CheckTree(t->right, event) || CheckTree(t->left, event);
}