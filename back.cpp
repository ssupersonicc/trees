#include <cmath>

#include "header.hpp"
extern int type;
extern std::vector<int> scale;

extern std::vector<double> scroll_coef_x;

Node* avl;
Node* rb;
Node* splay;
Node* treap;

// --------------------AVL-----------------------

void LeftRotate(Node*& t) {
  Node* p = t->right;
  if (p == nullptr) return;
  t->right = p->left;
  if (p->left != nullptr) p->left->parent = t;
  p->left = t;
  p->parent = t->parent;
  if (p->parent != nullptr) {
    if (p->parent->left == t) {
      p->parent->left = p;
    } else if (p->parent->right == t) {
      p->parent->right = p;
    }
  }
  t->parent = p;
  t = p;
  return;
}

void RightRotate(Node*& t) {
  Node* p = t->left;
  if (p == nullptr) return;
  t->left = p->right;
  if (p->right != nullptr) p->right->parent = t;
  p->right = t;
  p->parent = t->parent;
  if (p->parent != nullptr) {
    if (p->parent->left == t) {
      p->parent->left = p;
    } else if (p->parent->right == t) {
      p->parent->right = p;
    }
  }
  t->parent = p;
  t = p;
  return;
}

void BigLeftRotate(Node*& t) {
  Node* p = t->right;
  Node* q = p->left;
  t->right = q->left;
  if (q->left != nullptr) q->left->parent = t;

  p->left = q->right;
  if (q->right != nullptr) q->right->parent = p;
  q->left = t;
  q->right = p;

  q->parent = t->parent;
  t->parent = q;
  p->parent = q;

  if (q->parent != nullptr) {
    if (q->parent->left == t) {
      q->parent->left = q;
    } else if (q->parent->right == t) {
      q->parent->right = q;
    }
  }
  t = q;
  return;
}

void BigRightRotate(Node*& t) {
  Node* p = t->left;
  Node* q = p->right;
  t->left = q->right;
  if (q->right != nullptr) q->right->parent = t;

  p->right = q->left;
  if (q->left != nullptr) q->left->parent = p;

  q->right = t;
  q->left = p;

  q->parent = t->parent;
  t->parent = q;
  p->parent = q;

  if (q->parent != nullptr) {
    if (q->parent->left == t) {
      q->parent->left = q;
    } else if (q->parent->right == t) {
      q->parent->right = q;
    }
  }
  t = q;
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

void del_avl(Node*& t, Node*& p, long long num) {
  Node* q = delete_elem(p, num);
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
    t = q;
  }
  return;
}
// ---------------------RB-TREE---------------------

void fixInsertion(Node*& t, Node*& n) {
  if (n == nullptr) return;
  if (n->parent == nullptr) {
    n->nd.color = false;
    return;
  }
  Node* p = n->parent;
  if (!p->nd.color) {
    return;
  }
  Node* g = p->parent;
  Node* u = nullptr;
  if (g->left == p)
    u = g->right;
  else
    u = g->left;
  if (p->nd.color) {
    if (u != nullptr) {
      if (u->nd.color) {
        p->nd.color = false;
        u->nd.color = false;
        g->nd.color = true;
        fixInsertion(t, g);
        return;
      }
    }
    if (u == nullptr || !u->nd.color) {
      if (g->left == p && p->left == n) {
        g->nd.color = true;
        p->nd.color = false;
        RightRotate(g);
        if (g->parent == nullptr) t = g;
        return;
      } else if (g->right == p && p->right == n) {
        g->nd.color = true;
        p->nd.color = false;
        LeftRotate(g);
        if (g->parent == nullptr) t = g;
        return;
      } else if (g->left == p && p->right == n) {
        LeftRotate(p);
        fixInsertion(t, p->left);
        return;
      } else if (g->right == p && p->left == n) {
        RightRotate(p);
        fixInsertion(t, p->right);
        return;
      }
    }
  }
}

bool addRB(Node*& t, long long num) {
  Node* nlptr = nullptr;
  Node* q = insert(t, nlptr, num);
  while (t != nullptr && t->parent != nullptr) t = t->parent;
  if (q != nullptr) {
    q->nd.color = true;
    fixInsertion(t, q);
    return true;
  }
  return false;
}

void fixDeleting(Node*& t, Node*& n) {
  if (n->parent == nullptr && n->right == nullptr && n->left == nullptr) {
    t = nullptr;
    return;
  }
  if (n->nd.color) {
    if (n->parent != nullptr) {
      if (n->parent->left == n)
        n->parent->left = nullptr;
      else
        n->parent->right = nullptr;
    } else
      t = nullptr;
    return;
  }
  if (n->right == nullptr && n->left != nullptr) {
    Node* p = n->parent;
    n->left->nd.color = false;
    if (p != nullptr) {
      if (p->left == n)
        p->left = n->left;
      else
        p->right = n->left;
      n->left->parent = p;
    } else {
      t = n->left;
      n->left->parent = nullptr;
    }
    return;
  }
  if (n->right != nullptr && n->left == nullptr) {
    Node* p = n->parent;
    n->right->nd.color = false;
    if (p != nullptr) {
      if (p->left == n)
        p->left = n->right;
      else
        p->right = n->right;
      n->right->parent = p;
    } else {
      t = n->right;
      n->right->parent = nullptr;
    }
    return;
  }
  if (n->parent == nullptr) {
    return;
  }
  Node* p = n->parent;
  Node* s = nullptr;
  if (p->left == n)
    s = p->right;
  else
    s = p->left;
  Node* sr = s->right;
  Node* sl = s->left;
  if (!p->nd.color) {
    bool is_s = false;
    bool is_sr = false;
    bool is_sl = false;
    if (!s->nd.color) is_s = true;
    if (sl == nullptr)
      is_sl = true;
    else if (!sl->nd.color)
      is_sl = true;
    if (sr == nullptr)
      is_sr = true;
    else if (!sr->nd.color)
      is_sr = true;
    if (is_s && is_sl && is_sr) {
      s->nd.color = true;
      fixDeleting(t, p);
      if (n->parent->left == n)
        n->parent->left = nullptr;
      else
        n->parent->right = nullptr;
      return;
    }
  }
  if (p->nd.color) {
    bool is_s = false, is_sl = false, is_sr = false;
    if (!s->nd.color) is_s = true;
    if (sl == nullptr)
      is_sl = true;
    else if (!sl->nd.color)
      is_sl = true;
    if (sr == nullptr)
      is_sr = true;
    else if (!sr->nd.color)
      is_sr = true;
    if (is_s && is_sl && is_sr) {
      p->nd.color = false;
      s->nd.color = true;
      if (p->left == n)
        p->left = nullptr;
      else
        p->right = nullptr;
      return;
    }
  }
  if (!s->nd.color) {
    Node* anti = nullptr;
    Node* pro = nullptr;
    if (p->left == s) {
      anti = sl;
      pro = sr;
    } else {
      anti = sr;
      pro = sl;
    }
    if (anti != nullptr) {
      if (anti->nd.color) {
        s->nd.color = p->nd.color;
        p->nd.color = false;
        anti->nd.color = false;
        Node* g = p->parent;
        if (s->right == anti)
          LeftRotate(p);
        else
          RightRotate(p);
        p->parent = g;
        if (g != nullptr) {
          if (g->left == n->parent)
            g->left = p;
          else
            g->right = p;
        }
        if (n->parent->left == n)
          n->parent->left = nullptr;
        else
          n->parent->right = nullptr;
        return;
      }
    }
    if (anti == nullptr || !anti->nd.color) {
      if (pro != nullptr) {
        if (pro->nd.color) {
          pro->nd.color = false;
          s->nd.color = true;
          Node* s_temp = s;
          if (pro == s->left) {
            RightRotate(s);
          } else
            LeftRotate(s);
          if (p->right == s_temp)
            p->right = s;
          else
            p->left = s;
          s->parent = p;
          fixDeleting(t, n);
          if (n->parent->left == n)
            n->parent->left = nullptr;
          else
            n->parent->right = nullptr;
          return;
        }
      }
    }
  }
  if (s->nd.color) {
    p->nd.color = true;
    s->nd.color = false;
    Node* g = p->parent;
    if (s == p->right)
      LeftRotate(p);
    else
      RightRotate(p);
    p->parent = g;
    if (g != nullptr) {
      if (g->left = n->parent)
        g->left = p;
      else
        g->right = p;
    }
    fixDeleting(t, n);
    if (n->parent->left == n)
      n->parent->left = nullptr;
    else
      n->parent->right = nullptr;
    return;
  }
}

void del_rb(Node*& t, long long num) {
  Node* q = t;
  while (q->nd.num != num) {
    if (q->nd.num > num)
      q = q->left;
    else
      q = q->right;
  }
  Node* p = nullptr;
  if (q->right != nullptr && q->left != nullptr) {
    p = q->right;
    while (p->left != nullptr) p = p->left;
    std::swap(q->nd.num, p->nd.num);
  } else
    p = q;
  Node* tmp = p;
  fixDeleting(t, p);
  delete tmp;
  while (t != nullptr && t->parent != nullptr) t = t->parent;
  return;
}

//--------------------SPLAY---------------------------

void zigzig_right(Node*& t, Node*& q) {
  Node* p = q->parent;
  Node* g = p->parent;
  Node* qr = q->right;
  Node* pr = p->right;
  Node* root = g->parent;
  g->left = pr;
  if (pr != nullptr) pr->parent = g;
  p->right = g;
  g->parent = p;
  p->left = qr;
  if (qr != nullptr) qr->parent = p;
  q->right = p;
  p->parent = q;
  if (root == nullptr) {
    q->parent = nullptr;
    t = q;
  } else {
    q->parent = root;
    if (root->left == g)
      root->left = q;
    else
      root->right = q;
  }
  return;
}

void zigzig_left(Node*& t, Node*& q) {
  Node* p = q->parent;
  Node* g = p->parent;
  Node* ql = q->left;
  Node* pl = p->left;
  Node* root = g->parent;
  g->right = pl;
  if (pl != nullptr) pl->parent = g;
  p->left = g;
  g->parent = p;
  p->right = ql;
  if (ql != nullptr) ql->parent = p;
  q->left = p;
  p->parent = q;
  if (root == nullptr) {
    t = q;
    q->parent = nullptr;
  } else {
    q->parent = root;
    if (root->left == g)
      root->left = q;
    else
      root->right = q;
  }
  return;
}

void zigzag_right(Node*& t, Node*& q) {
  Node* ql = q->left;
  Node* qr = q->right;
  Node* p = q->parent;
  Node* g = p->parent;
  Node* root = g->parent;
  p->right = ql;
  if (ql != nullptr) ql->parent = p;
  g->left = qr;
  if (qr != nullptr) qr->parent = g;
  q->left = p;
  p->parent = q;
  q->right = g;
  g->parent = q;
  if (root == nullptr) {
    t = q;
    q->parent = nullptr;
  } else {
    q->parent = root;
    if (root->left == g)
      root->left = q;
    else
      root->right = q;
  }
  return;
}

void zigzag_left(Node*& t, Node*& q) {
  Node* ql = q->left;
  Node* qr = q->right;
  Node* p = q->parent;
  Node* g = p->parent;
  Node* root = g->parent;
  p->left = qr;
  if (qr != nullptr) qr->parent = p;
  g->right = ql;
  if (ql != nullptr) ql->parent = g;
  q->left = g;
  g->parent = q;
  q->right = p;
  p->parent = q;
  if (root == nullptr) {
    t = q;
    q->parent = nullptr;
  } else {
    q->parent = root;
    if (root->left == g)
      root->left = q;
    else
      root->right = q;
  }
  return;
}

void zig_right(Node*& t, Node*& q) {
  Node* qr = q->right;
  Node* p = q->parent;
  p->left = qr;
  if (qr != nullptr) qr->parent = p;
  q->right = p;
  p->parent = q;
  q->parent = nullptr;
  t = q;
  return;
}

void zig_left(Node*& t, Node*& q) {
  Node* ql = q->left;
  Node* p = q->parent;
  p->right = ql;
  if (ql != nullptr) ql->parent = p;
  q->left = p;
  p->parent = q;
  q->parent = nullptr;
  t = q;
  return;
}

Node* splay_find(Node*& t, Node*& prev, long long num) {
  if (t == nullptr) return prev;
  if (t->nd.num == num) return t;
  if (t->nd.num > num) {
    return splay_find(t->left, t, num);
  } else
    return splay_find(t->right, t, num);
}

void Splay(Node*& t, Node* q) {
  if (q == nullptr) return;
  if (q->parent == nullptr) return;
  Node* p = q->parent;
  Node* g = p->parent;
  if (g == nullptr) {
    if (p->left == q)
      zig_right(t, q);
    else
      zig_left(t, q);
  } else {
    if (p->left == q && g->left == p)
      zigzig_right(t, q);
    else if (p->right == q && g->right == p)
      zigzig_left(t, q);
    else if (p->right == q && g->left == p)
      zigzag_right(t, q);
    else if (p->left == q && g->right == p)
      zigzag_left(t, q);
    Splay(t, q);
  }
  return;
}

std::pair<Node*, Node*> splay_split(Node*& t, long long num) {
  Node* nll = nullptr;
  Node* q = splay_find(t, nll, num);
  if (q != nullptr) {
    Splay(t, q);
    if (t->nd.num >= num) {
      Node* t1 = t->left;
      t->left = nullptr;
      if (t1 != nullptr) t1->parent = nullptr;
      return {t1, t};
    } else {
      Node* t2 = t->right;
      t->right = nullptr;
      if (t2 != nullptr) t2->parent = nullptr;
      return {t, t2};
    }
  }
  return {nullptr, nullptr};
}

Node* splay_merge(Node*& t1, Node*& t2) {
  Node* q = t2;
  while (q != nullptr && q->left != nullptr) {
    q = q->left;
  }
  Splay(t2, q);
  if (t2 != nullptr) {
    t2->left = t1;
    if (t1 != nullptr) t1->parent = t2;
    return t2;
  }
  return t1;
}

bool add_splay(Node*& t, long long num) {
  std::pair<Node*, Node*> sp = splay_split(t, num);
  if (sp.second == nullptr || sp.second->nd.num != num) {
    Node* q = new Node;
    q->nd.num = num;
    q->nd.wt = -1;
    q->nd.color = false;
    q->left = nullptr;
    q->right = nullptr;
    q->parent = nullptr;
    q->left = sp.first;
    if (sp.first != nullptr) sp.first->parent = q;
    q->right = sp.second;
    if (sp.second != nullptr) sp.second->parent = q;
    t = q;
    return true;
  }
  return false;
}

void del_splay(Node*& t, long long num) {
  Node* nll = nullptr;
  Node* q = splay_find(t, nll, num);
  Splay(t, q);
  Node* r = t->right;
  Node* l = t->left;
  Node* tmp = t;
  if (l != nullptr) l->parent = nullptr;
  if (r != nullptr) r->parent = nullptr;
  t = splay_merge(l, r);
  delete tmp;
}

// -------------------TREAP-----------------------------
bool exist = false;

std::pair<Node*, Node*> treap_split(Node*& t, long long num) {
  if (t == nullptr) return {nullptr, nullptr};
  if (t->nd.num < num) {
    std::pair<Node*, Node*> q = treap_split(t->right, num);
    t->right = q.first;
    if (q.first != nullptr) {
      q.first->parent = t;
    }
    if (t != nullptr) t->parent = nullptr;
    if (q.second != nullptr) q.second->parent = nullptr;
    return {t, q.second};
  } else {
    std::pair<Node*, Node*> q = treap_split(t->left, num);
    t->left = q.second;
    if (q.second != nullptr) {
      q.second->parent = t;
    }
    if (q.first != nullptr) q.first->parent = nullptr;
    if (t != nullptr) t->parent = nullptr;
    return {q.first, t};
  }
}

Node* treap_merge(Node*& l, Node*& r) {
  if (l == nullptr) return r;
  if (r == nullptr) return l;
  if (l->nd.wt > r->nd.wt) {
    Node* q = treap_merge(l->right, r);
    l->right = q;
    if (q != nullptr) q->parent = l;
    return l;
  } else {
    Node* q = treap_merge(l, r->left);
    r->left = q;
    if (q != nullptr) q->parent = r;
    return r;
  }
}

bool addTreap(Node*& k, long long num) {
  bool ans = false;
  auto ret = treap_split(k, num);
  Node* t1 = ret.first;
  Node* t2 = ret.second;
  if (!exist) {
    Node* it = new Node;
    it->nd.num = num;
    it->nd.wt = rand() % 1000;
    it->left = nullptr;
    it->right = nullptr;
    it->parent = nullptr;
    t2 = treap_merge(it, t2);
    ans = true;
  }
  k = treap_merge(t1, t2);
  exist = false;
  return ans;
}

Node* del_treap(Node*& t, long long num) {
  std::pair<Node*, Node*> sp = treap_split(t, num);
  Node* v = sp.second;
  Node* q = sp.second;
  while (q->left != nullptr) q = q->left;

  Node* p = q->right;
  if (q->parent != nullptr)
    q->parent->left = p;
  else
    v = p;
  if (p != nullptr) p->parent = q->parent;
  return treap_merge(sp.first, v);
}

//--------------------------------------------------------
Node* delete_elem(Node*& t, long long num) {
  if (t == nullptr) return nullptr;
  if (num < t->nd.num) {
    return delete_elem(t->left, num);
  } else if (num > t->nd.num) {
    return delete_elem(t->right, num);
  }
  Node* p = t->right;
  if (p == nullptr) {
    p = t;
    if (t->left != nullptr) t->left->parent = t->parent;
    t = t->left;
    Node* ans = p->parent;
    delete p;
    return ans;
  }
  while (p->left != nullptr) {
    p = p->left;
  }
  std::swap(p->nd, t->nd);
  return delete_elem(t->right, num);
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
  bool is_add = false;
  if (type == 1)
    is_add = addAVL(avl, num);
  else if (type == 2)
    is_add = addRB(rb, num);
  else if (type == 3) {
    is_add = add_splay(splay, num);
  } else if (type == 4)
    is_add = addTreap(treap, num);

  if (is_add) {
    Restructuring(type);
  }
  return;
}

int HReverse(Node* t) {
  if (t == nullptr) return 0;
  return HReverse(t->parent) + 1;
}

void Restructuring(int type) {
  Node* t = nullptr;
  if (type == 1)
    t = avl;
  else if (type == 2)
    t = rb;
  else if (type == 3)
    t = splay;
  else if (type == 4)
    t = treap;
  double r = 8 * scale[type - 1];
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
    if (i == H - 1) {
      if (coord[i].first < 0)
        scroll_coef_x[type - 1] = fabs(coord[i].first) / 610.0;
      else
        scroll_coef_x[type - 1] = 0;
    }
  }
  Update(t, 50, 1, coord);
  return;
}
