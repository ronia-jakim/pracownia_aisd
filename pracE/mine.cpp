#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second
const int MAKS = 1e3 + 5;
pair<int,int> uf[MAKS][MAKS];
int sajz[MAKS][MAKS];
int wyspy;
int n,m,t;
vector<int> queries;
vector<int> ans;
vector<pair<int, pair<int,int>>> potop;
void input() {
    cin >> n >> m; 
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int x; cin >> x;
            potop.push_back({x,{i,j}});
        }
    }
    cin >> t;
    for(int i = 1; i <= t; i++) {
        int x; cin >> x;
        queries.push_back(x);
    }
}


void init() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            uf[i][j] = {i, j};
        }
    }
}

pair<int,int> szuk(pair<int,int> x) {
    auto z = uf[x.f][x.s];
    if(z == x) return x;
    uf[x.f][x.s] = szuk(z);
    return uf[x.f][x.s];
}

void loncz(pair<int,int> a, pair<int,int> b) {
    a = szuk(a); b = szuk(b);
    if(a == b) return;
    wyspy--;
    if(sajz[a.f][a.s] < sajz[b.f][b.s]) swap(a,b);
    sajz[a.f][a.s] += sajz[b.f][b.s];
    uf[b.f][b.s] = a;
}

void debug() {
    for(int i = 1; i<= n; i++) {
        for(int j = 1; j<= m; j++) {
            if(sajz[i][j]) {
            cout << uf[i][j].f * 10 + uf[i][j].s << " ";
            }
            else cout << "00 ";
        }
        cout << "\n";
    }
}
void solve() {
    while(queries.size()) {
        while(potop.size() && potop.back().f > queries.back()) {
            auto p = potop.back(); potop.pop_back();
            int h= p.f; auto cord = p.s; int x = p.s.f; int y = p.s.s;
            sajz[x][y] = 1;
            wyspy++;
            if(x > 1 && sajz[x-1][y]) {
                loncz(cord, {x-1, y});
            }
            if(x < n && sajz[x+1][y]) {
                loncz(cord, {x+1, y});
            }
            if(y > 1 && sajz[x][y-1]) {
                loncz(cord, {x, y-1});
            }
            if(y < n && sajz[x][y+1]) {
                loncz(cord, {x, y+1});
            }
        }
        if(0) {
            cout << wyspy <<"\n";
            debug();
        }
        queries.pop_back();
        ans.push_back(wyspy);
    }
}
void wypisz() {
    reverse(ans.begin(), ans.end());
    for(int x : ans) {
        cout << x << " ";
    }
}

int main() {
    input();
    init();
    sort(potop.begin(), potop.end());
    solve();
    wypisz();
}
