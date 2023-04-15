#include<iostream>
#include<vector>

using namespace std;

#define ll long long

int n, m, k;

#define S 1000001
#define MAX 9999999999999

vector<int> drogi[S]; // jak zapamietywac krawedzie?
//int docelowe[S];

//ll odleglosc[S];

//int odwiedzone[S];

pair<int, ll> kolejka[S];
int kolejka_size;

void insert(int v, ll dst);
void delete_min();
void debug();

int main () {
    kolejka_size = 0;

    cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        int a, b, d;

        cin >> a >> b >> d;
        //drogi[a][b] = d;
        //drogi[b][a] = d;
    }

    /*for (int i = 0; i < k; i++) {
        cin >> docelowe[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            odleglosc[i][j] = MAX;
        }
        odwiedzone[i] = 0;
    }
    */

    return 0;
}

void debug() {
    cout << "ZAWARTOSC KOLEJKI:\n";

    for (int i = 0; i < kolejka_size; i++) {
        cout << "[ " << kolejka[i].first << " : " << kolejka[i].second << " ] ";
    }

    cout << "\n\n";
}

void insert (int v, ll dst) {
    int pos = kolejka_size;
    kolejka[pos] = make_pair(v, dst);

    while (kolejka[pos/2].second > kolejka[pos].second) {
        pair<int, ll> pom = kolejka[pos/2];
        kolejka[pos/2] = kolejka[pos];
        kolejka[pos] = pom;
        pos /= 2;
    }
    kolejka_size++;
}

void delete_min() {
    kolejka[0] = kolejka[kolejka_size-1];

    kolejka[kolejka_size - 1] = make_pair(0, 0);

    if (kolejka[0].second < kolejka[1].second) return;

    int pos = 0;

    while (kolejka[pos].second > kolejka[pos*2+1].second && pos*2+1 < kolejka_size) {
        pair<int, ll> pom = kolejka[pos];
        kolejka[pos] = kolejka[pos*2+1];
        kolejka[pos*2+1] = pom;
        pos *= 2;
        pos++;
    }

    kolejka_size--;
}
