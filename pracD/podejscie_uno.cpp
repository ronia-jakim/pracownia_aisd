#include <iostream>

using namespace std;

#define ll long long

struct drzewo {
  ll value;
  drzewo * rodzic;
  drzewo * lewy;
  drzewo * prawy;

  bool kolor; // chyba true to czerwone, ale oczywiscie kurwa nie zapisalam za wczasu
};

struct dupsko {
  drzewo * korzen;
};

string gorka (ll x, drzewo * t, string ret);
string womwuz (ll x, drzewo * t, string ret);

void lewa_rotacja (drzewo * t);
void prawa_rotacja (drzewo * t);

void insert(ll x);
void insert_repair (drzewo * t);

void przeszczep (drzewo * t, drzewo * r);

string wypierdol (ll x);
void wpierdol (drzewo * t);
void popraw_wpierdol (drzewo * t);

void debug(drzewo * d);

dupsko DUPA; // zawsze ma na poczatku 0 :<
int n;

int bylo_zero;

int main() {
  //DUPA.rodzic = nullptr;
  //DUPA.lewy = nullptr;
  //DUPA.prawy = nullptr;

  bylo_zero = false;

  cin >> n;

  while (n > 0) {
    char c;
    ll x;
    cin >> c;
    cin >> x;

    if (c == 'I') {
      insert(x);
    }
    else if (c == 'D') {
      cout << wypierdol(x);
    }
    else if (c == 'L') cout << womwuz (x, DUPA.korzen, "BRAK");
    else if (c == 'U') cout << gorka (x, DUPA.korzen, "BRAK");

    if (c != 'I') cout << "\n";
    n--;

    //if (bylo_zero) cout << "BYLO\n";
    //else cout << "ni bylo\n";

    //debug(&DUPA);
    //cout << endl;
  }
}

void debug (drzewo * d) {
  if (d != NULL) {
    debug(d->lewy);
    cout << d->value << " ";
    debug(d->prawy);
  }
}

string gorka (ll x, drzewo * t, string ret) { // najmniejsza wieksza
  if (t == NULL) {
    return ret;
  }

  if (x == t->value) {
    return to_string(x);
  }
  
  if (x > t->value) return gorka(x, t->prawy, ret);
  
  // if x < t->value
  return gorka(x, t->lewy, to_string(t->value));
}

string womwuz (ll x, drzewo * t, string ret) { // najwieksza mniejsza
  if (t == NULL) return ret;

  if (x == t->value) {
    return to_string(x);
  }

  if (x < t->value) return womwuz(x, t->lewy, ret);

  // x > t->value
  return womwuz(x, t->prawy, to_string(t->value));
}

void insert (ll x) {
  //cout << "KURWA COS?\n";
  drzewo * temp = DUPA.korzen;
  drzewo * prev = nullptr;

  if (x == 0) bylo_zero = true;

  int l = 1;

  while (temp != NULL) {
    //cout << "ODWIEDZAM " << temp->value << " ";

    if (temp->value == x) return;

    prev = temp;
    
    if (temp->value > x) {
      temp = temp->lewy;
      l = 1;
    }
    else {
      temp = temp->prawy;
      l = 0;
    }
  }

  //cout << endl;

  drzewo * lisc = new drzewo;
  lisc->value = x;
  lisc->lewy = nullptr;
  lisc->prawy = nullptr;
  lisc->kolor = true;
  lisc->rodzic = prev;
  
  if (l == 1) prev->lewy = lisc;
  else prev->prawy = lisc;

  insert_repair(lisc);
}
  
void lewa_rotacja (drzewo * t) {
  drzewo * pom = t->prawy;
  t->prawy = pom->lewy;

  if (pom->lewy != NULL) {
    pom->lewy->rodzic = t;
  }
  pom->rodzic = t->rodzic;

  if (t->rodzic == NULL) DUPA.korzen = pom;
  else if (t == t->rodzic->lewy) t->rodzic->lewy = pom;
  else t->rodzic->prawy = pom;
  pom->lewy = t;
  t->rodzic = pom;
}

void prawa_rotacja (drzewo * t) {
  drzewo * pom = t->lewy;
  t->lewy = pom->prawy;

  if (pom->prawy != NULL) {
    pom->prawy->rodzic = t;
  }
  pom->rodzic = t->rodzic;

  if (t->rodzic == NULL) DUPA.korzen = pom;
  else if (t == t->rodzic->prawy) t->rodzic->prawy = pom;
  else t->rodzic->lewy = pom;
  pom->prawy = t;
  t->rodzic = pom;
}

void insert_repair (drzewo * t) {
  drzewo * wujek;

  while (t->rodzic->kolor && t != nullptr) {
    //cout << "AAA\n";

    if (t->rodzic == t->rodzic->rodzic->prawy) {
      //cout << "uno\n";
      wujek = t->rodzic->rodzic->lewy;
      //cout << " mm\n";
      if (wujek == nullptr) return;

      if (wujek->kolor) {
        //cout << "A\n";
        wujek->kolor = false;
        t->rodzic->kolor = false;
        t->rodzic->rodzic->kolor = true;

        t = t->rodzic->rodzic;
      }
      else {
        //cout << "B\n";
        if (t == t->rodzic->lewy) {
          t = t->rodzic;

          //cout << "TUTAJ\n";

          prawa_rotacja(t);
        }

        t->rodzic->kolor = false;
        t->rodzic->rodzic->kolor = true;
        lewa_rotacja(t->rodzic->rodzic);
      }
    }
    else {
      wujek = t->rodzic->rodzic->prawy;

      if(wujek->kolor) {
        wujek->kolor = false;
        t->rodzic->kolor = false;
        t->rodzic->rodzic->kolor = true;
        
        t = t->rodzic->rodzic;
      }
      else {
        if (t == t->rodzic->prawy) {
          t = t->rodzic;
          //cout << "KURWAAA\n";
          lewa_rotacja(t);
        }

        t->rodzic->kolor = false;
        t->rodzic->rodzic->kolor = true;
        prawa_rotacja(t->rodzic->rodzic);
      }
    }
  }
  DUPA.korzen->kolor = false;
}

void przeszczep (drzewo * t, drzewo * r) {
  if (t->rodzic == nullptr) DUPA.korzen = r;
  else if (t == t->rodzic->lewy) t->rodzic->lewy = r;
  else t->rodzic->prawy = r;

  r->rodzic = t->rodzic;

}

string wypierdol (ll x) {
  drzewo * t = DUPA.korzen;
  //cout << "AA\n";

  while (t != nullptr) {
    if (t->value == x) break;
    else if (t->value > x) t = t->lewy;
    else t = t->prawy;
  }
  //cout << "AAA\n";
  
  if (t == nullptr) return "BRAK";
  //cout << "AAAAA\n";

  wpierdol (t);
  //cout << "DUPA\n";
  return "OK";
}

void wpierdol (drzewo * t) {
  drzewo * y = t;
  bool y_col = t->kolor;

  //cout << "g\n";

  drzewo * x;

  //cout << "dupa\n";

  if (t->lewy == nullptr) {
    //cout << "mm\n";
    x = t->prawy;
    przeszczep(t, t->prawy);
    //cout << "chuj\n";
  }
  else if (t->prawy == nullptr) {
    y_col = y->kolor;
    x = y->prawy;
  
    //cout << "chuj^2\n";

    if (y->rodzic == t) x->rodzic = y;
    else {
      przeszczep(y, y->prawy);
      y->prawy = t->prawy;
      y->prawy->rodzic = y;
    }
    //cout << "killme\n";
    przeszczep(t, y);
    y->lewy = t->lewy;
    y->lewy->rodzic = y;
    y->kolor = t->kolor;
    //cout << "glowa mnie boli\n";
  }

  if (y_col == false) popraw_wpierdol(x);

  delete(t);
}

void popraw_wpierdol (drzewo * t) {
  while (t != DUPA.korzen && t->kolor == false) {
    drzewo * w;
    if (t == t->rodzic->lewy) {
      w = t->rodzic->prawy;
      
      if (w->kolor) {
        w->kolor = false;
        t->rodzic->kolor = true;
        lewa_rotacja(t->rodzic);
        w = t->rodzic->prawy;
      }

      if (w->lewy->kolor == false && w->prawy->kolor == false) {
        w->kolor = true;
        t = t->rodzic;
      }
      else if (w->prawy->kolor == false) {
        w->lewy->kolor = false;
        w->kolor = true;
        prawa_rotacja(w);
        w = t->rodzic->prawy;
      }
      
      w->kolor = t->rodzic->kolor;
      t->rodzic->kolor = false;
      w->prawy->kolor = false;
      lewa_rotacja(t->rodzic);

      t = DUPA.korzen;
    }
    else {
      w = t->rodzic->lewy;
      
      if (w->kolor) {
        w->kolor = false;
        t->rodzic->kolor = true;
        lewa_rotacja(t->rodzic);
        w = t->rodzic->lewy;
      }

      if (w->prawy->kolor == false && w->lewy->kolor == false) {
        w->kolor = true;
        t = t->rodzic;
      }
      else if (w->lewy->kolor == false) {
        w->prawy->kolor = false;
        w->kolor = true;
        lewa_rotacja(w);
        w = t->rodzic->lewy;
      }
      
      w->kolor = t->rodzic->kolor;
      t->rodzic->kolor = false;
      w->lewy->kolor = false;
      prawa_rotacja(t->rodzic);

      t = DUPA.korzen;
    }
  }
  t->kolor = false;
}
