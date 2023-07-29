#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>

using namespace std;

#define ll long long

int n;
int GORA = 10000002;
ll ret;
vector<pair<int, tuple<int, int, int>>> archiwumX;

const int MAXN = 100001;
int AAA[4*MAXN];

struct node {
  int a, b;

  node * left;
  node * right;

  ll max;
};

node * new_node (int w, int beg, int end);
void insert_tree (int w, int y1, int y2, node * t);

int main () {
  ret = 0;
  cin >> n;

  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2, w;
    cin >> x1 >> y1 >> x2 >> y2 >> w;
    archiwumX.push_back(make_pair(x1, make_tuple(y1, y2, w)));
    archiwumX.push_back(make_pair(x2, make_tuple(y1, y2, -w)));
  }

  sort(archiwumX.begin(), archiwumX.end());

  //ll ret = 0;

  node * tree = new_node(0, -1, GORA);

  /*for (int i = 0; i < archiwumX.size(); i++) {
    int x = archiwumX[i].first;
    tuple<int, int, int> d = archiwumX[i].second;
    cout << x << " < " << get<0>(d) << ", " << get<1>(d) << ", " << get<2>(d) << " >\n";
  }*/

  pair<int, tuple<int, int, int>> prev = archiwumX[archiwumX.size()-1];
  tuple<int, int, int> tup_prev = prev.second;
  int x_prev = prev.first;

  while (!archiwumX.empty()) {
    pair<int, tuple<int, int, int>> WELES = archiwumX[archiwumX.size()-1];
    archiwumX.pop_back();

    int x_coord = WELES.first;
    tuple<int, int, int> tup_now = WELES.second;
    
    //cout << x_coord << " < " << get<0>(tup_now) << ", " << get<1>(tup_now) << ", " << get<2>(tup_now) << " > || ";
    //cout << x_prev << " < " << get<0>(tup_prev) << ", " << get<1>(tup_prev) << ", " << get<2>(tup_prev) << " >\n";

    if (x_coord != x_prev) {
      if (ret < tree->max) ret = tree->max;
      tree = new_node(0, -1, GORA);
    }

    insert_tree(get<2>(tup_now), get<0>(tup_now), get<1>(tup_now), tree);
    x_prev = x_coord;
    tup_prev = tup_now;

    if (ret < tree->max) ret = tree->max;
  }

  cout << ret << endl;

  return 0;
}

node * new_node (int w, int beg, int end) {
  node * n = new node;
  
  n->left = n->right = NULL;

  n->max = w;

  n->a = beg;
  n->b = end;
  
  return n;
}

void insert_tree (int w, int y1, int y2, node * t) {
  int a = t->a;
  int b = t->b;
  int mid = (a+b)/2;

  if (a >= b) return;

  if (y1 <= a && b <= y2) {
    if (w < 0) {
      t->max -= w;
      ret = max(t->max, ret);
      t->max += w;
    }
    t->max += w;
    ret = max(t->max, ret);
  }
  else {
    if (y1 < mid) {
      if (t->left == NULL) t->left = new_node(t->max, a, mid);
      insert_tree(w, y1, y2, t->left);
      //t->max = max(t->max, t->left->max);
      ret = max(t->left->max, ret);
    }
    if (mid < y2) {
      if (t->right == NULL) t->right = new_node(t->max, mid, b);
      insert_tree(w, y1, y2, t->right);
      //t->max = max(t->max, t->right->max);
      ret = max(t->right->max, ret);
    }
  }
}
