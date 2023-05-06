#include <iostream>

using namespace std;

#define ll long long

struct drzewo {
  ll value;
  drzewo * rodzic;
  drzewo * lewy;
  drzewo * prawy;

  drzewo * korzen;

  bool kolor;
};

string gorka (ll x, drzewo * t, string ret);
string womwuz (ll x, drzewo * t, string ret);

void lewa_rotacja (drzewo * t);
void prawa_rotacja (drzewo * t);

void insert(ll x);
drzewo * insert_tree (ll x, drzewo * t, drzewo * p);
void insert_repair (drzewo * t);

drzewo DUPA; // zawsze ma na poczatku 0 :<

int main() {
  DUPA.korzen = &DUPA;
  DUPA.rodzic = nullptr;
  DUPA.lewy = nullptr;
  DUPA.prawy = nullptr;

  /*DUPA = *(insert(2, &DUPA, nullptr));
  cout << "AAA\n";
  //DUPA = *DUPA.prawy;

  DUPA = *(insert(8, &DUPA, nullptr));
  cout << "cos\n";
  DUPA = *(insert(1, &DUPA, nullptr));
  DUPA = *(insert(9, &DUPA, nullptr));
  DUPA = *(insert(2, &DUPA, nullptr));

  cout << DUPA.prawy->value << DUPA.prawy->kolor << "\n";
  cout << DUPA.prawy->lewy->value << DUPA.prawy->lewy->kolor << " " << DUPA.prawy->prawy->value << DUPA.prawy->prawy->kolor << "\n";
  cout << DUPA.prawy->prawy->prawy->value << DUPA.prawy->prawy->prawy->kolor << " \n";
  */

  insert(6);
  insert(2);
  insert(8);
  insert(9);
  insert(1);

  cout << DUPA.value << " \n" << DUPA.prawy->value << "n" << DUPA.prawy->kolor << "\n";
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

  if (x > t->value) return womwuz(x, t->lewy, to_string(t->value));

  // if x < t->value
  return womwuz(x, t->prawy, ret);
}

void insert (ll x) {
  drzewo * temp = insert_tree(x, &DUPA, nullptr);

  if (temp == NULL) return;

  insert_repair(temp);
}

drzewo * insert_tree (ll x, drzewo * t, drzewo * p) {
  if (t == NULL) {
    t = new drzewo;
    t->rodzic = p;
    t->value = x;
    t->prawy = NULL;
    t->lewy = NULL;
    t->kolor = true;
    t->korzen = p->korzen;
    return t;
  }
  if (t->value == x) return nullptr;
    //return t;

  if (t->value < x) {
    //t->prawy = insert(x, t->prawy, t);
    return insert_tree(x, t->prawy, t);
  }
  else {
    //t->lewy = insert(x, t->lewy, t);
    return insert_tree(x, t->lewy, t);
  }
  //return t;
}

void lewa_rotacja (drzewo * t) {
  drzewo * pom = t->prawy;
  t->prawy = pom->lewy;

  if (pom->lewy != NULL) {
    pom->lewy->rodzic = t;
  }
  pom->rodzic = t->rodzic;
  if (t->rodzic != NULL) {
    if (t == t->rodzic->lewy) t->rodzic->lewy = pom;
    else t->rodzic->prawy = pom;
    pom->lewy = t;
    t->rodzic = pom;
  }
}

void prawa_rotacja (drzewo * t) {
  drzewo * pom = t->lewy;
  t->lewy = pom->prawy;

  if (pom->prawy != NULL) {
    pom->prawy->rodzic = t;
  }
  pom->rodzic = t->rodzic;
  if (t->rodzic != NULL) {
    if (t == t->rodzic->prawy) t->rodzic->prawy = pom;
    else t->rodzic->lewy = pom;
    pom->prawy = t;
    t->rodzic = pom;
  }
}

void insert_repair (drzewo * t) {
  if (t == t->korzen) return;


  drzewo * dziadek = t->rodzic->rodzic;
  drzewo * ojciec = t->rodzic;

  if (ojciec->kolor == false) return;

  if (ojciec == dziadek->lewy) {
    drzewo * wujek = dziadek->prawy;

    if (wujek->kolor == true) {
      dziadek->kolor = true;
      wujek->kolor = false;
      ojciec->kolor = false;

      insert_repair(dziadek);
    }
    else {
      if (wujek->kolor == false && t == ojciec->prawy) {
        t = ojciec;
        ojciec = t->rodzic;
        dziadek = ojciec->rodzic;
        if (dziadek->prawy == ojciec) wujek = dziadek->lewy;
        else wujek = dziadek->prawy;
        lewa_rotacja(t);
      }
      ojciec->kolor = false;
      dziadek->kolor = true;
      prawa_rotacja (dziadek);
    }
  }
  else {
    drzewo * wujek = dziadek->lewy;

    if (wujek->kolor == true) {
      dziadek->kolor = true;
      wujek->kolor = false;
      ojciec->kolor = false;

      insert_repair(dziadek);
    }
    else {
      if (wujek->kolor == false && t == ojciec->lewy) {
        t = ojciec;
        ojciec = t->rodzic;
        dziadek = ojciec->rodzic;
        if (dziadek->prawy == ojciec) wujek = dziadek->lewy;
        else wujek = dziadek->prawy;
        prawa_rotacja(t);
      }
      ojciec->kolor = false;
      dziadek->kolor = true;
      lewa_rotacja (dziadek);
    }
  }
}
