#include<iostream>
#include<vector>

// można max 2 razy pod rząd w górę
// graf skierowany? topo sortem znajduję możliwe ścieżki startujące z każdej możliwej na pierwszym rzędzie i szukam najdłuższej ścieżki?
// złożoność to chyba jakieś n * log n + n?

#define ll long long int

using namespace std;

int w, k;

int potega[10];

ll DUPEK [13][10000][2];


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
                DUPEK[13][j][1] = potega[pom];
            //cout << pom << " " << g << " \n";
            ll dd = 0;
            // z gory skacze na to co jestem
            int orgia = 0;
            if (i > 0) {
                if (j > 1) {
                    dd = DUPEK[12][j-2][0];
                    orgia = -2;
                }
                if (j < k-2) {
                    //dd = max(DUPEK[12][j+2], dd);
                    if (dd < DUPEK[12][j+2][0]) {
                        orgia = 2;
                        dd = DUPEK[12][j+2][0];
                    }
                }
            }
            if (i > 1) {
                if (j > 0) {
                    if (dd < DUPEK[11][j-1][0]) {
                        dd = DUPEK[11][j-1][0];
                        orgia = -1;
                    }
                }
                if (j < k-1) {
                    if (dd < DUPEK[11][j+1][0]) {
                        dd = DUPEK[11][j+1][0];
                        orgia = 1;
                    }
                }
            }
            DUPEK[13][j][0] = dd + potega[pom];

            // skacze do gory i wracam :3
            ll t = DUPEK[13][j][0];
            if (i > 0) {
                if (j > 1 && orgia != -2) DUPEK[12][j-2][0] = max(t+DUPEK[12][j-2][1], DUPEK[12][j-2][0]);
                if (j < k-2 && orgia != 2) DUPEK[12][j+2][0] = max(t+DUPEK[12][j+2][1], DUPEK[12][j+2][0]);
            }
            if (i > 1) {
                if (j > 0 && orgia != -1) DUPEK[11][j-1][0] = max(t+DUPEK[12][j-1][1], DUPEK[12][j-1][0]);
                if (j < k-1 && orgia != 1) DUPEK[11][j+1][0] = max(t+DUPEK[12][j+1][1], DUPEK[12][j+1][0]);
            }
        }
        for (int j = 0; j < k; j++) {
            DUPEK[11][j][0] = DUPEK[12][j][0];
            DUPEK[11][j][1] = DUPEK[12][j][1];
            DUPEK[12][j][0] = DUPEK[13][j][0];
            DUPEK[12][j][1] = DUPEK[13][j][1];
        }
    }

    ll ret = 0;
    for (int i = 0; i < k; i++) {
        if (ret < DUPEK[13][i][0]) ret = DUPEK[13][i][0];
    }

    cout << ret << "\n";

    return 0;
}






