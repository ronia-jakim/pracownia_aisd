#include<iostream>
#include<vector>
#include<algorithm>

#define ll long long

using namespace std;

const int MAX = 1002;
const int CHUJ = 100069;

int n, m;
pair<int, pair<int, int>> wyspa [MAX][MAX]; // pierwsza wartosc to wysokosc, druga to wpsolrzedne rodzica?
vector<pair<int, pair<int, int>>> gorki;

int T;
//int zapytanka [CHUJ]; // to juz jest podane rosnaco
//int odpowiedzi [CHUJ];
vector<int> zapytanka;
vector<int> odpowiedzi;

int ziemia;

bool sortowanko(pair<int, int> a, pair<int, int>);

void socjalistyczna_republika (pair<int, int> a, pair<int, int> b);
pair<int, int> cheka (pair<int, int> a);

int main () {
  //std::ios::sync_with_stdio(false);
  //cin.tie(NULL);

  ziemia = 0;

  cin >> n >> m;

  //cout << "DUPA\n";

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int pom;
      cin >> pom;

      pair<int, int> coord = make_pair(i, j);

      wyspa[i][j] = make_pair(pom, coord);
      gorki.push_back(make_pair(pom, coord));
      //cout << gorki.back().first << " " << gorki.back().second << "\n";
    }
  }

  //cout << "KURWA\n";

  sort(gorki.begin(), gorki.end());//, sortowanko);

  //cout << "PIZDA\n";

  cin >> T;

  //cout << "CHUJ\n";

  for (int i = 0; i < T; i++) {
    int pom;
    cin >> pom;
    zapytanka.push_back(pom);
    //zapytanka[i] = pom;
  }

  int najnizej = gorki.size() - 1;

  //cout << "dupa\n";

  for (int t = T-1; t >= 0; t--) {
    int zalew = zapytanka[t];

    while (najnizej >= 0 && wyspa[gorki[najnizej].second.first][gorki[najnizej].second.second].first > zalew && najnizej >= 0) {

      pair<int, int> coord = gorki[najnizej].second;
      int x = coord.first;
      int y = coord.second;

      pair<int, int> p = wyspa[x][y].second;

      ziemia++;

      if (x+1 < n && wyspa[x+1][y].first > zalew) {
        socjalistyczna_republika(make_pair(x+1, y), coord);
      }
      if (x > 0 && wyspa[x-1][y].first > zalew) {
        socjalistyczna_republika(make_pair(x-1, y), coord);
      }
      if (y+1 < m && wyspa[x][y+1].first > zalew) {
        socjalistyczna_republika(make_pair(x, y+1), coord);
      }
      if (y > 0 && wyspa[x][y-1].first > zalew) {
        socjalistyczna_republika(make_pair(x, y-1), coord);
      }

      najnizej--;
    }
    //cout << ziemia << "\n";

    odpowiedzi.push_back(ziemia);
    //odpowiedzi[t] = ziemia;
  }

  for (int i = T-1; i>=0 ; i--) cout << odpowiedzi[i] << " ";
  //for(int i = 0; i < T; i++) cout << odpowiedzi[i] << " ";

  cout << "\n";

  return 0;
}

bool sortowanko (pair<int, int> a, pair<int, int> b) {
  //cout << "SKURWIEL\n";
  //cout << a.first << " " << a.second << " ^-^ " << b.first << " " << b.second << ":<\n";
  if (wyspa[a.first][a.second].first <= wyspa[b.first][b.second].first) return true;
  return false;
}

pair<int, int> cheka (pair<int, int> a) {
  int x = a.first;
  int y = a.second;

  pair<int, int> p = wyspa[x][y].second;

  if (x == p.first && y == p.second) return a;
  
  pair<int, int> ret = cheka(p);
  wyspa[x][y].second = ret;
  return ret;
}

void socjalistyczna_republika (pair<int, int> a, pair<int, int> b) {
  a = cheka(a);
  b = cheka(b);

  int x = b.first;
  int y = b.second;
  if (a.first != b.first || a.second != b.second) {
    ziemia--;

    int h = wyspa[x][y].first;
    wyspa[x][y] = make_pair(h, a);
  }
}
