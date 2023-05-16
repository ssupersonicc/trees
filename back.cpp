#include <cmath>

#include "header.hpp"
extern int type;
extern int scale;

Node* avl;
Node* rb;
Node* splay;
Node* treap;

// --------------------AVL-----------------------

void LeftRotate(Node*& t) {
  Node* p = t->right;
  t->right = p->left;
  p->left = t;
  t = p;

  t->parent = t->left->parent;
  if (t->parent != nullptr) {
    if (t->parent->left == t->left)
      t->parent->left = t;
    else if (t->parent->right == t->left)
      t->parent->right = t;
  }
  t->left->parent = t;
  if (t->left->right != nullptr) t->left->right->parent = t->left;
  return;
}

void RightRotate(Node*& t) {
  Node* p = t->left;
  t->left = p->right;
  p->right = t;
  t = p;

  t->parent = t->right->parent;
  if (t->parent != nullptr) {
    if (t->parent->left == t->right)
      t->parent->left = t;
    else if (t->parent->right == t->right)
      t->parent->right = t;
  }
  t->right->parent = t;
  if (t->right->left != nullptr) t->right->left->parent = t->right;
  return;
}

void BigLeftRotate(Node*& t) {
  Node* p = t->right;
  Node* q = p->left;
  t->right = q->left;
  p->left = q->right;
  q->left = t;
  q->right = p;
  t = q;

  t->parent = t->left->parent;
  if (t->parent != nullptr) {
    if (t->parent->left == t->left)
      t->parent->left = t;
    else if (t->parent->right == t->left)
      t->parent->right = t;
  }
  t->right->parent = t;
  t->left->parent = t;
  if (t->left->right != nullptr) t->left->right->parent = t->left;
  if (t->right->left != nullptr) t->right->left->parent = t->right;
  return;
}

void BigRightRotate(Node*& t) {
  Node* p = t->left;
  Node* q = p->right;
  t->left = q->right;
  p->right = q->left;
  q->right = t;
  q->left = p;
  t = q;

  t->parent = t->right->parent;
  if (t->parent != nullptr) {
    if (t->parent->left == t->right)
      t->parent->left = t;
    else if (t->parent->right == t->right)
      t->parent->right = t;
  }
  t->right->parent = t;
  t->left->parent = t;
  if (t->right->left != nullptr) t->right->left->parent = t->right;
  if (t->left->right != nullptr) t->left->right->parent = t->left;
  return;
}

bool addAVL(Node*& T, long long num) {
  Node* nll = nullptr;
  Node* q = insert(T, nll, num);
  if (q == nullptr) return false;
  while (q != nullptr) {
    int h1 = h(q->left);
    int h2 = h(q->right);
    if (abs(h1 - h2) == 2) {
      if (h1 > h2) {
        int c = h(q->left->right);
        int l = h(q->left->left);
        if (c <= l)
          RightRotate(q);
        else
          BigRightRotate(q);
      } else if (h2 > h1) {
        int c = h(q->right->left);
        int r = h(q->right->right);
        if (c <= r)
          LeftRotate(q);
        else
          BigLeftRotate(q);
      }
    }
    if (q->parent == nullptr) break;
    q = q->parent;
  }
  T = q;
  return true;
}

void del_avl(Node*& t) {
  Node* q = delete_elem(t);
  if (q != nullptr) {
    while (q != nullptr) {
      int h1 = h(q->left);
      int h2 = h(q->right);
      if (abs(h1 - h2) == 2) {
        if (h1 > h2) {
          int c = h(q->left->right);
          int l = h(q->left->left);
          if (c <= l)
            RightRotate(q);
          else
            BigRightRotate(q);
        } else if (h2 > h1) {
          int c = h(q->right->left);
          int r = h(q->right->right);
          if (c <= r)
            LeftRotate(q);
          else
            BigLeftRotate(q);
        }
      }
      if (q->parent == nullptr) break;
      q = q->parent;
    }
  }
  return;
}

//--------------------------------------------------------
Node* delete_elem(Node*& t) {
  Node* p = t->right;
  if (p == nullptr) {
    Node* q = t;
    if (t->left != nullptr) t->left->parent = t->parent;
    // проверить является ли t->left поддеревом t->parent
    t = t->left;
    if (q->parent != nullptr) {
      if (q->parent->left == q)
        q->parent->left = nullptr;
      else if (q->parent->right == q)
        q->parent->right = nullptr;
    }
    Node* ans = q->parent;
    delete q;
    return ans;
  }
  while (p->left != nullptr) {
    p = p->left;
  }
  std::swap(p->nd, t->nd);
  return delete_elem(p);
}

Node* insert(Node*& T, Node*& prev, long long num) {
  if (T == nullptr) {
    T = new Node;
    T->left = nullptr;
    T->right = nullptr;
    T->parent = prev;
    T->nd.color = false;
    T->nd.num = num;
    T->nd.wt = -1;
    return T;
  }
  if (num > T->nd.num)
    return insert(T->right, T, num);
  else if (num < T->nd.num)
    return insert(T->left, T, num);
  else
    return nullptr;
}

int h(Node* t) {
  if (t == nullptr) return 0;
  return std::max(h(t->right), h(t->left)) + 1;
}

void Add(long long num, sf::RenderWindow& window) {
  if (type == 1) {
    bool is_add = addAVL(avl, num);
    if (is_add) {
      Restructuring(type);
    }
  }
  return;
}

int HReverse(Node* t) {
  if (t == nullptr) return 0;
  return HReverse(t->parent) + 1;
}

void Restructuring(int type) {
  Node* t = nullptr;
  if (type == 1) t = avl;
  double r = 10 * scale;
  int H = h(t);
  int count = (1 << (H - 1));
  int p = 2;
  std::vector<std::pair<double, double>> coord(H);
  for (int i = H - 1; i >= 0; --i) {
    int dr = ((1 << p) - 2) * r;
    if (i == 0) {
      dr = 0;
    }
    coord[i].first = 640 - dr / 2 - count * r - dr * (count / 2 - 1);
    coord[i].second = dr;
    count /= 2;
    ++p;
  }
  Update(avl, 50, 1, coord);
  return;
}
