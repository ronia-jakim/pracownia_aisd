#include<iostream>

#define ll long long

int GORA = 10000002;

struct node {
  int a, b;

  ll max;

  node * left;
  node * right;

  node * y;
};

struct dzewo {
  node * korzen;
  node * PUSTAK;
};

using namespace std;

dzewo KRZYS;

int n;

node * new_node(int w, int a, int b);
void insertX (node * t, int x1, int y1, int x2, int y2, int w);
void insertY (node * t, int y1, int y2, int w); 
int main () {
  cin >> n;

  KRZYS.korzen = new node;
  KRZYS.korzen->a = -1;
  KRZYS.korzen->b = GORA;
  KRZYS.korzen->max = 0;

  KRZYS.PUSTAK = KRZYS.korzen;
  KRZYS.korzen->left = KRZYS.korzen->right = KRZYS.korzen->y = KRZYS.PUSTAK;

  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2, w;
    cin >> x1 >> y1 >> x2 >> y2 >> w;

    insertX(KRZYS.korzen, x1, y1, x2, y2, w);
    //cout << KRZYS.korzen->max << endl;
  }

  cout << KRZYS.korzen->max << "\n";

  return 0;
}

node * new_node(int w, int a, int b) {
  node * n = new node;

  n->left = n->right = n->y = KRZYS.PUSTAK;

  n->a = a;
  n->b = b;

  n->max = w;

  return n;
}

void insertX (node * t, int x1, int y1, int x2, int y2, int w) {
  int a = t->a;
  int b = t->b;
  int mid = (a+b)/2;

  if (x1 <= a && b <= x2) { // przedzial jest pokrywany
    if (t->y == KRZYS.PUSTAK) t->y = new_node(0, -1, GORA);
    insertY(t->y, y1, y2, w);
    t->max = max(t->max, t->y->max);
  }
  else { // jakas czesc przedzialu node jest poza tym prostokatem co go wstawiam
    if (x1 < mid) { // zachacza o lewa czesc node'a
      if (t->left == KRZYS.PUSTAK) t->left = new_node(t->max, a, mid);
      insertX(t->left, x1, y1, x2, y2, w);
      t->max = max(t->max, t->left->max);
    }
    if (mid < x2) { // zachacza o prawa czesc node'a
      if (t->right == KRZYS.PUSTAK) t->right = new_node(t->max, mid, b);
      insertX(t->right, x1, y1, x2, y2, w);
      t->max = max(t->max, t->right->max);
    }
  }
}

void insertY (node * t, int y1, int y2, int w) {
  int a = t->a;
  int b = t->b;
  int mid = (a+b)/2;

  if (y1 <= a && b <= y2) {
    t->max += w;
  }
  else {
    if (y1 < mid) {
      if (t->left == KRZYS.PUSTAK) t->left = new_node(t->max, a, mid);
      insertY(t->left, y1, y2, w);
      t->max = max(t->max, t->left->max);
    }
    if (mid < y2) {
      if (t->right == KRZYS.PUSTAK) t->right = new_node(t->max, mid, b);
      insertY(t->right, y1, y2, w);
      t->max = max(t->max, t->right->max);
    }
  }
}
