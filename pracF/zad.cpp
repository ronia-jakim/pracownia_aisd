#include<iostream>
#include<vector>

#define ll long long

using namespace std;

int n;
int GORA = 10000001;

struct node {
  int begg;
  int end;

  //int pivot;

  node * left;
  node * right;

  node * y;
  ll max;
};

struct dzewo {
  node * korzen;
  node * PUSTAK;
};

void insert (int o, int x1, int y1, int x2, int y2, node * t);
void insertY(int o, int y1, int y2, node * t);

dzewo TREE;

int main () {
  cin >> n;

  TREE.korzen = new node;
  TREE.korzen->begg = -1;
  TREE.korzen->end = GORA;
  TREE.korzen->max = 0;

  TREE.PUSTAK = TREE.korzen;
  TREE.korzen->left = TREE.PUSTAK;
  TREE.korzen->right = TREE.PUSTAK;
  TREE.korzen->y = TREE.PUSTAK;


  //node TREE;
  //TREE.begg = -1;
  //TREE.end = GORA;

  //node * ptrT = &TREE;

  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int w;
    cin >> w;
    //cout << x1 << endl;
    insert(w, x1, y1, x2, y2, TREE.korzen);
  }

  cout << TREE.korzen->max << endl;
}


void insertY (int o, int y1, int y2, node * t) {
  if (t->end < t->begg) return;

  if (y1 <= t->begg && t->end <= y2) {
    t->max += o;
  }
  else {
    int sep = (t->end + t->begg)/2;

    if (y1 < sep) {
      if (t->left == TREE.PUSTAK) {
        node * n = new node;
        n->begg = t->begg;
        n->end = (t->begg + t->end)/2;
        n->max = t->max;
        n->left = TREE.PUSTAK;
        n->right = TREE.PUSTAK;

        t->left = n;
      }
      insertY(o, y1, y2, t->left);
      t->max = max(t->max, t->left->max);
    }

    if(sep < y2) {
      if (t->right == TREE.PUSTAK) {
        node * n = new node;
        n->begg = (t->begg + t->end) / 2;
        n->end = t->end;
        n->max = t->max;
        n->left = TREE.PUSTAK;
        n->right = TREE.PUSTAK;

        t->right = n;
      }
      insertY(o, y1, y2, t->right);
      t->max = max(t->max, t->right->max);
    }
  }
}

void insert (int o, int x1, int y1, int x2, int y2, node * t) {
  if (t->end < t->begg) return;

  if (x1 <= t->begg && t->end <= x2) {
    if (t->y == TREE.PUSTAK) {
      node * n = new node;
      n->begg = 0;
      n->end = GORA;
      n->max = 0;
      n->left = TREE.PUSTAK;
      n->right = TREE.PUSTAK;

      t->y = n;
    }
    insertY(o, y1, y2, t->y);
    t->max = max(t->max, t->y->max);
  }
  else {
    int sep = (t->end + t->begg)/2;
    if (x1 < sep) {
      if (t->left == TREE.PUSTAK) {
        node * n = new node;
        n->begg = t->begg;
        n->end = (t->begg + t->end) / 2;
        n->max = t->max;
        n->left = TREE.PUSTAK;
        n->right = TREE.PUSTAK;
        n->y = TREE.PUSTAK;

        t->left = n;
      }
      insert(o, x1, y1, x2, y2, t->left);
      t->max = max(t->max, t->left->max);
    }
    if (sep < x2) {
      if (t->right == TREE.PUSTAK) {
        node * n = new node;
        n->begg = (t->begg + t->end) / 2;
        n->end = t->end;
        n->max = t->max;
        n->left = TREE.PUSTAK;
        n->right = TREE.PUSTAK;
        n->y = TREE.PUSTAK;

        t->right = n;

      }
      insert(o, x1, y1, x2, y2, t->right);
      t->max = max(t->max, t->right->max);
    }
  }
}
