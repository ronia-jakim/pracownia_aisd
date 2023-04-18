#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define ll long long

int n, m, k;

const int S = 1e5;
const ll MAX = 1e9+9;
const int bit14 = 16383 << 17;
const int bit17 = 131071;// << 14;

vector<int> drogi[S];
//int drogi[S][S];
//int docelowe[S];
//
//bool bylo[S][S];

ll odleglosc[S];

//int odwiedzone[S];

int kolejka[S];
int kolejka_size;
int dupa[S];

void insert(int v);
void delete_min();
void debug();
void swappp(int a, int b);
void bring_order(int pos);

int code(int index, int dst);
int decode(int v);

int main () {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    //cout << "DUPA: " << bit14 << " " << bit17 << "\n";
    
    kolejka_size = 0;

    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        dupa[i] = -1;
    }


    for (int i = 0; i < m; i++) {
        int a, b, d;

        cin >> a >> b >> d;
        a--;
        b--;
        
        drogi[a].push_back(code(b, d));
        drogi[b].push_back(code(a, d));
        //drogi[a].push_back(make_pair(b, d));
        //drogi[b].push_back(make_pair(a, d));
    }

    /*for (int i = 0; i < k; i++) {
        cin >> docelowe[i];
        docelowe[i]--;
    }*/

    odleglosc[0] = 0;
    insert(0);

    for (int i = 1; i < n; i++) {
        odleglosc[i] = MAX;
        //insert(i);
    }

    //debug();

    while (kolejka_size > 0) {
        int u = kolejka[0];
        delete_min();

        //debug();

        for (int i = 0; i < drogi[u].size(); i++) {
            int v = drogi[u][i] & bit17;
            //drogi[u][i].first;
            ll alt = odleglosc[u] + decode(drogi[u][i]);
            //drogi[u][i].second;
            if (alt < odleglosc[v]) {
                odleglosc[v] = alt;
                //cout << "--- " << v << " " << dupa[v] << "---\n";
                insert(v);
            }
        }
    }

    //debug();

    
    ll ret = 0;

    for (int i = 0; i < k; i++) {
        int l;
        cin >> l;
        ll pom = odleglosc[l-1];
        if (pom >= MAX) {
            cout << "NIE\n";
            return 0;
        }
        ret += pom;
    }
    
    cout << ret * 2 << "\n";

    return 0;
}

void debug() {
    cout << "ZAWARTOSC KOLEJiKI: " << kolejka_size << "\n";

    for (int i = 0; i < kolejka_size; i++) {
        cout << "[ " << kolejka[i] << " : " << odleglosc[kolejka[i]] << " " << i << " " << dupa[kolejka[i]] <<  " ] ";
    }

    cout << "\n\n";

    cout << "ZAWARTOSC ODLEGLOSC:\n";

    for (int i = 0; i < n; i++) {
        cout << odleglosc[i] << " ";
    }
    cout << "\n\n";

    cout << "ZAWARTOSC DUPA:\n";
    
    for (int i = 0; i < n; i++) {
        cout << dupa[i] << " ";
    }
    cout << "\n\n";
}

void insert (int v) {
//cout << "===insert " << dupa[v] << " ===\n";
//debug();
    if (dupa[v] == -1) {
        int pos = kolejka_size;
        kolejka[pos] = v;
        dupa[v] = pos;

        while (odleglosc[kolejka[(pos-1)/2]] > odleglosc[kolejka[pos]]) {
            swappp(pos, (pos-1)/2);
            pos--;
            pos /= 2;
        }
        kolejka_size++;
    }
    else bring_order(dupa[v]);
}

void bring_order(int pos) {
//cout << "===bring_order()===\n";
//debug();
    while (pos >= 0) {
        if (odleglosc[kolejka[(pos-1)/2]] > odleglosc[kolejka[pos]]) {
            swappp((pos-1)/2, pos);
            pos = (pos-1)/2;
        }
        else return;
    }
}

void delete_min() {
//    cout << "\n\nDELETE_MIN " << kolejka[0] << " " << kolejka[kolejka_size-1] << "\n";
    dupa[kolejka[0]] = -1;
    kolejka[0] = kolejka[kolejka_size-1];

    kolejka[kolejka_size - 1] = 0;
    kolejka_size--;
    dupa[kolejka[0]] = 0;

    if (odleglosc[kolejka[0]] < odleglosc[kolejka[1]]) return;
    
    int pos = 0;

    while (pos * 2 + 2 < kolejka_size) {
        if (odleglosc[kolejka[pos*2 + 1]] < odleglosc[kolejka[pos]]) {
            swappp(pos, pos*2+1);
            pos = pos * 2 + 1;
        }
        else if (odleglosc[kolejka[pos*2+2]] < odleglosc[kolejka[pos]]) {
            swappp(pos, pos*2+2);
            pos = pos * 2 + 2;
        }
        else return;
    }
}

void swappp (int a, int b) {
    int pom = kolejka[a];
    dupa[kolejka[a]] = b;
    dupa[kolejka[b]] = a;
    kolejka[a] = kolejka[b];
    kolejka[b] = pom;

    //dupa[kolejka[a]] = b;
    //dupa[kolejka[b]] = a;
}

int decode (int v) {
    return ((v & bit14) >> 17);
}
int code (int index, int dst) {
    return ((index & bit17) | ((dst << 17) & bit14));
}
