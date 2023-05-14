#include "header.hpp"
extern int type;

Node* avl;
Node* rb;
Node* splay;
Node* treap;

void LeftRotate(Node*& t) {
  Node* p = t->right;
  t->right = p->left;
  p->left = t;
  t = p;

  t->parent = t->left->parent;
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
  t->left->parent = t;
  t->right->parent = t;
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
  t->right->parent = t;
  t->left->parent = t;
  if (t->right->left != nullptr) t->right->left->parent = t->right;
  if (t->left->right != nullptr) t->left->right->parent = t->left;
  return;
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

void addAVL(Node*& T, long long num) {
  Node* nll = nullptr;
  Node* q = insert(T, nll, num);
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
  return;
}

void Add(long long num) {
  if (type == 1) {
    addAVL(avl, num);
  }
  return;
}