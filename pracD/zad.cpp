#include<iostream>

using namespace std;

#define ll long long

struct wezelek {
  ll wartosc;

  wezelek * rodzic;
  wezelek * lewy;
  wezelek * prawy;

  bool kolor; // true znaczy, że czerwone
};

struct drzewko {
  wezelek * korzen;
  wezelek * dupa;
};

drzewko DUPA;
int n;

void debug (wezelek * t);

string upper_limit (ll x, wezelek * t, string ret);
string lower_limit (ll x, wezelek * t, string ret);

wezelek * tree_min (wezelek * t);

void left_rotate (wezelek * t);
void right_rotate (wezelek * t);

void insert (ll x);
void fix_insert (wezelek * t);

void transplant (wezelek * u, wezelek * v);
string remove (ll x);
void remove_tree (wezelek * t);
void fix_delete (wezelek * t);

int main () {
  std::ios::sync_with_stdio(false);
  cin.tie(NULL);

  DUPA.dupa = new wezelek;
  DUPA.dupa->kolor = false;
  DUPA.dupa->rodzic = DUPA.dupa;
  DUPA.dupa->lewy = DUPA.dupa;
  DUPA.dupa->prawy = DUPA.dupa;

  DUPA.korzen = DUPA.dupa;

  cin >> n;

  char pom;
  ll x;

  //cout << n << "\n";

  for (int i = 0; i < n; i++) {
    //cout << "kurwa?\n";
    cin >> pom;
    cin >> x;

    //cout << pom << " " << x << "\n";

    if (pom == 'I') insert(x);
    else {
      if (pom == 'D') cout << remove(x);
      if (pom == 'L') cout << lower_limit(x, DUPA.korzen, "BRAK");
      if (pom == 'U') cout << upper_limit(x, DUPA.korzen, "BRAK");

      cout << "\n";
    }
    //debug(DUPA.korzen);
    //cout << "OK\n";
  }
  //cout << "\n";
}


void debug (wezelek * t) {
  if (t->lewy != DUPA.dupa) debug(t->lewy);
  if (t != DUPA.dupa) cout << t->wartosc << " ";
  if (t->prawy != DUPA.dupa) debug(t->prawy);
}

//=====================================================================================//
//==========              GRANICE                                          ============//
//=====================================================================================//

string upper_limit (ll x, wezelek * t, string ret) { // najmniejsze wieksze
  //cout << "DUUUPA\n";
  if (t == DUPA.dupa) return ret;
  
  if (t->wartosc == x) return to_string(x);

  if (t->wartosc > x) return upper_limit(x, t->lewy, to_string(t->wartosc));
  
  // t->wartosc < x
  return upper_limit(x, t->prawy, ret);
}

string lower_limit (ll x, wezelek * t, string ret) { // najwieksze mniejsze
  //cout << "DUPA\n";
  if (t == DUPA.dupa) return ret;

  if (t->wartosc == x) return to_string(x);

  if (t->wartosc < x) return lower_limit(x, t->prawy, to_string(t->wartosc));

  return lower_limit(x, t->lewy, ret);
}

wezelek * tree_min (wezelek * t) {
  while (t->lewy != DUPA.dupa) t = t->lewy;
  return t;
}

//=====================================================================================//
//==========              ROTACJE                                          ============//
//=====================================================================================//

void left_rotate (wezelek * t) {
  wezelek * y = t->prawy;

  t->prawy = y->lewy;
  if (y->lewy != DUPA.dupa) y->lewy->rodzic = t;
  
  y->rodzic = t->rodzic;

  if (t->rodzic == DUPA.dupa) DUPA.korzen = y;
  else if (t == t->rodzic->lewy) t->rodzic->lewy = y;
  else t->rodzic->prawy = y;

  y->lewy = t;
  t->rodzic = y;
  //cout << "LEWAK?\n";
}


void right_rotate (wezelek * t) {
  wezelek * y = t->lewy;

  t->lewy = y->prawy;
  if (y->prawy != DUPA.dupa) y->prawy->rodzic = t;
  
  y->rodzic = t->rodzic;

  if (t->rodzic == DUPA.dupa) DUPA.korzen = y;
  else if (t == t->rodzic->prawy) t->rodzic->prawy = y;
  else t->rodzic->lewy = y;

  y->prawy = t;
  t->rodzic = y;
  //cout << "PRAWAK?\n";
}

//=====================================================================================//
//==========              WSTAWIANIE                                       ============//
//=====================================================================================//

void insert (ll x) {
  wezelek * t = DUPA.korzen;
  wezelek * y = DUPA.dupa;

  wezelek * n = new wezelek;
  n->wartosc = x;
  n->lewy = DUPA.dupa;
  n->prawy = DUPA.dupa;
  n->kolor = true;

  while (t != DUPA.dupa) {
    //cout << t->wartosc << " | " << y->wartosc << "\n";
    y = t;
    if (t->wartosc == x) return;
    if (n->wartosc < t->wartosc) t = t->lewy;
    else t = t->prawy;
  }

  n->rodzic = y;

  if (y == DUPA.dupa) DUPA.korzen = n;
  else if (n->wartosc < y->wartosc) y->lewy = n;
  else y->prawy = n;

  if (n->rodzic == DUPA.dupa) {
    n->kolor = false;
    return;
  }
  if (n->rodzic->rodzic == DUPA.dupa) return;

  fix_insert(n);
}

void fix_insert (wezelek * t) {
  wezelek * y;

  //cout << "AAAAAA\n";

  while (t->rodzic->kolor) {
    //cout << "cokolwiek\n";
    //cout << t->rodzic->rodzic->wartosc << "\n";
    //cout << t->wartosc << "||\n";
    if (t->rodzic == t->rodzic->rodzic->prawy) {
      //cout << "U\n";
      y = t->rodzic->rodzic->lewy;
      //cout << "mynio\n";

      if (y->kolor) {
        t->rodzic->kolor = false;
        y->kolor = false;
        t->rodzic->rodzic->kolor = true;
        t = t->rodzic->rodzic;
        //cout << "A\n";
      }
      else {
        if (t == t->rodzic->lewy) {
          t = t->rodzic;
          right_rotate(t);
          //cout << "B\n";
        }
      
        t->rodzic->kolor = false;
        t->rodzic->rodzic->kolor = true;
        left_rotate(t->rodzic->rodzic);
        //cout << "C\n";
      }
    }
    else {
      //cout << "I\n";

      y = t->rodzic->rodzic->prawy;
      //cout << "pysio\n";

      if (y->kolor) {
        t->rodzic->kolor = false;
        y->kolor = false;
        t->rodzic->rodzic->kolor = true;
        t = t->rodzic->rodzic;
        //cout <<"DUPa\n";
      }
      else {
        if (t == t->rodzic->prawy) {
          t = t->rodzic;
          left_rotate(t);
        }
      
        t->rodzic->kolor = false;
        t->rodzic->rodzic->kolor = true;
        right_rotate(t->rodzic->rodzic);
      }
    }
    //cout << "tutaj?\n";
    if (t == DUPA.korzen) break;
  }

  DUPA.korzen->kolor = false;
}

//=====================================================================================//
//==========                USUWANIE                                       ============//
//=====================================================================================//

void transplant (wezelek * u, wezelek * v) {
  if (u->rodzic == DUPA.dupa) DUPA.korzen = v;
  else if (u == u->rodzic->lewy) {
    u->rodzic->lewy = v;
  }
  else u->rodzic->prawy = v;

  v->rodzic = u->rodzic;

  //delete(u);
}

string remove (ll x) {
  wezelek * t = DUPA.korzen;

  wezelek * kubelek = DUPA.dupa;

  while (t != DUPA.dupa) {
    if (t->wartosc == x) kubelek = t;
    
    if (t->wartosc > x) t = t->lewy;
    else t = t->prawy;
  }

  if (kubelek == DUPA.dupa) return "BRAK";

  remove_tree(kubelek);

  delete(kubelek);

  return "OK";
}

void remove_tree (wezelek * t) {
  wezelek * y = t;
  wezelek * x;

  bool y_col = y->kolor;

  if (t->lewy == DUPA.dupa) {
    x = t->prawy;
    transplant(t, t->prawy);
  }
  else if (t->prawy == DUPA.dupa) {
    x = t->lewy;
    transplant(t, t->lewy);
  }
  else {
    y = tree_min(t->prawy);
    y_col = y->kolor;
    x = y->prawy;

    if (y->rodzic == t) x->rodzic = y;
    else {
      transplant(y, y->prawy);
      y->prawy = t->prawy;
      y->prawy->rodzic = y;
    }

    wezelek * l = t->lewy;
    bool k = t->kolor;

    transplant(t, y);
    
    y->lewy = l;
    y->lewy->rodzic = y;
    y->kolor = k;
  }

  if (y_col == false) fix_delete(x);
}

void fix_delete (wezelek * t) {
  wezelek * w;

  while (t != DUPA.korzen && t->kolor == false) {
    if (t == t->rodzic->lewy) {
      w = t->rodzic->prawy;

      if (w->kolor) {
        w->kolor = false;
        t->rodzic->kolor = true;
        left_rotate(t->rodzic);
        w = t->rodzic->prawy;
      }

      if (w->lewy->kolor == false && w->prawy->kolor == false) {
        w->kolor = true;
        t = t->rodzic;
      }
      else {
        if (w->prawy->kolor == false) {
          w->lewy->kolor = false;
          w->kolor = true;
          right_rotate(w);
          w = t->rodzic->prawy;
        }

        w->kolor = t->rodzic->kolor;
        t->rodzic->kolor = false;
        w->prawy->kolor = false;
        left_rotate(t->rodzic);
        t = DUPA.korzen;
      }
    }
    else {
      w = t->rodzic->lewy;

      if (w->kolor) {
        w->kolor = false;
        t->rodzic->kolor = true;
        left_rotate(t->rodzic);
        w = t->rodzic->lewy;
      }

      if (w->prawy->kolor == false && w->lewy->kolor == false) {
        w->kolor = true;
        t = t->rodzic;
      }
      else {
        if (w->lewy->kolor == false) {
          w->prawy->kolor = false;
          w->kolor = true;
          left_rotate(w);
          w = t->rodzic->lewy;
        }

        w->kolor = t->rodzic->kolor;
        t->rodzic->kolor = false;
        w->lewy->kolor = false;
        right_rotate(t->rodzic);
        t = DUPA.korzen;
      }
    }
  }
}
