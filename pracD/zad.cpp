#include <iostream>

using namespace std;

#define ll long long

struct drzewo {
  ll value;
  drzewo * rodzic;
  drzewo * lewy;
  drzewo * prawy;

  bool kolor;
};

string gorka (ll x, drzewo * t, string ret);
string womwuz (ll x, drzewo * t, string ret);

void lewa_rotacja (drzewo * t);
void prawa_rotacja (drzewo * t);

void insert(ll x);
void insert_repair (drzewo * t);

void debug(drzewo * d);

drzewo DUPA; // zawsze ma na poczatku 0 :<
int n;

int main() {
  DUPA.rodzic = nullptr;
  DUPA.lewy = nullptr;
  DUPA.prawy = nullptr;

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
      cout << "CHWILOWO BRAK\n";
    }
    else if (c == 'L') cout << womwuz (x, &DUPA, "BRAK");
    else if (c == 'U') cout << gorka (x, &DUPA, "BRAK");

    if (c != 'I') cout << "\n";
    n--;
  }
}

void debug (drzewo * d) {
  if (d != NULL) {
    debug(d->lewy);
    cout << d->value << " ";
    debug(d->prawy);
  }
}

string gorka (ll x, drzewo * t, string ret) {
  // min y \in t y >= x
  if (t == NULL) {
    return ret;
  }
  
  if (x == t->value) return to_string(x);
  
  if (x > t->value) return gorka(x, t->prawy, ret);
  
  // if x < t->value
  return gorka(x, t->lewy, to_string(t->value));
}

string womwuz (ll x, drzewo * t, string ret) {
  if (t == NULL) return ret;

  if (x == t->value) return to_string(x);

  if (x < t->value) return womwuz(x, t->lewy, ret);

  // x > t->value
  return womwuz(x, t->prawy, to_string(t->value));
}

void insert (ll x) {
  //cout << "KURWA COS?\n";
  drzewo * temp = &DUPA;
  drzewo * prev = nullptr;

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

  if (t->rodzic == NULL) DUPA = *pom;
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

  if (t->rodzic == NULL) DUPA = *pom;
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
  DUPA.kolor = false;
}
