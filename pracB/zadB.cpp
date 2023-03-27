#include<iostream>
#include<vector>

// można max 2 razy pod rząd w górę
// graf skierowany? topo sortem znajduję możliwe ścieżki startujące z każdej możliwej na pierwszym rzędzie i szukam najdłuższej ścieżki?
// złożoność to chyba jakieś n * log n + n?

#define ll long long int

using namespace std;

int w, k;

int potega[10];

ll DUPEK [18][10000][2];


int main () {
    // std::ios::sync_with_stdio(false);
    // cin.tie(NULL);
    //
    potega[0] = 1;
    for (int i = 1; i < 10; i++) {
        potega[i] = potega[i-1] * 7;
    }
        
    cin >> w >> k;

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < k; j++) {
            int pom;
            char g;
            cin >> g;
            pom = int(g) - 48;

            DUPEK[5][j] += potega[pom];

            if (j > 0) DUPEK[7][j-1][0] = max(DUPEK[7][j-1][0], DUPEK[5][j]);
            if (j > 1) DUPEK[6][j-2][0] = max(DUPEK[6][j-2][0], DUPEK[5][j]);
            if (j < k-1) DUPEK[7][j+1] = max(DUPEK[7][j+1], DUPEK[5][j]);
            if (j < k-2) DUPEK[6][j+2] = max(DUPEK[6][j+2], DUPEK[5][j]);

            if (j < k-2) DUPEK[5][j+2] = max(DUPEK[5][j+2], DUPEK[5][j] + DUPEK[3][j+1]);
            if (j < k-5) DUPEK[5][j+4] = max(DUPEK[5][j] + DUPEK[4][j+2], DUPEK[5][j+4]);
            if (j < k-4) DUPEK[6][j+3] = max(DUPEK[5][j] + DUPEK[4][j+2], DUPEK[6][j+3]);
            if (j < k-3) DUPEK[6][j+1] = max(DUPEK[5][j] + DUPEK[4][j+2], DUPEK[6][j+1]);
            if (j > 1) DUPEK[6][j-1] = max(DUPEK[5][j] + DUPEK[4][j-2], DUPEK[6][j-1]);
            if (j > 2) DUPEK[6][j-3] = max(DUPEK[5][j] + DUPEK[4][j-2], DUPEK[6][j-2]);

        }
        for (int j = 0; j < k; j++) {
            for (int l = 0; l < 8; l++) DUPEK[l][j] = DUPEK[l+1][j];
        }
    }

    ll ret = 0;
    for (int i = 0; i < k; i++) {
        if (ret < DUPEK[4][i]) ret = DUPEK[4][i];
    }

    cout << ret << "\n";

    return 0;
}






