#include<iostream>
#include<vector>

// można max 2 razy pod rząd w górę
// graf skierowany? topo sortem znajduję możliwe ścieżki startujące z każdej możliwej na pierwszym rzędzie i szukam najdłuższej ścieżki?
// złożoność to chyba jakieś n * log n + n?

#define ll long long int

using namespace std;

int w, k;

int potega[10];

ll DUPEK [18][10000];
int POT[18][10000];

int main () {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    //
    potega[0] = 1;
    for (int i = 1; i < 10; i++) {
        potega[i] = potega[i-1] * 7;
    }
        
    cin >> w >> k;

    for (int i = 0; i < w; i++) {
        if (k == 2 && i % 2 == 1) continue;
        for (int j = 0; j < k; j++) {
            int pom;
            char g;
            cin >> g;
            pom = int(g) - 48;

            POT[5][j] = potega[pom];
        }
        for (int j = 0; j < k; j++) {

            int krok[2][2] = {{2, 1}, {2, -1}};
            
            DUPEK[5][j] = 0;

            for (int m = 0; m < 2; m++) {
                if (0 <= j+krok[m][1] && j+krok[m][1] < k) {
                    int x = 5-krok[m][0];
                    int y = j+krok[m][1];
                    for (int l = 0; l < 2; l++) {
                        if (0 <= y+krok[l][1] && y+krok[l][1] < k) {
                            int a = 5-krok[m][0]-krok[l][0];
                            int b = j+krok[m][1]+krok[l][1];
 
                            DUPEK[5][j] = max(DUPEK[5][j], DUPEK[a][b] + POT[x][y]);
                        }
                    }
                }
            }                    
            
            if (i % 2 == 1) {
                if (j + 2 >= k || j-2 < 0) DUPEK[5][j] = 0;
            }

            if (i >= 3){
                if (j+1 < k && j-1 >= 0) {
                    DUPEK[5][j] = max(DUPEK[5][j], DUPEK[4][j+1] + POT[3][j-1]);
                }
                if (j-3 >= 0) {
                    DUPEK[5][j] = max(DUPEK[5][j], DUPEK[4][j-3] + POT[3][j-1]);
                }

                if (j-1 >= 0 && j+1 < k) {
                    DUPEK[5][j] = max(DUPEK[5][j], DUPEK[4][j-1] + POT[3][j+1]);
                }
                if (j+3 < k) {
                    DUPEK[5][j] = max(DUPEK[5][j], DUPEK[4][j+3] + POT[3][j+1]);
                }
            }

            if (i >= 1) {
                if (j+2 < k) {
                    DUPEK[4][j+2] = max(DUPEK[4][j+2], DUPEK[5][j]+POT[4][j+2]);
                }
                if (j-2 >= 0) {
                    DUPEK[4][j-2] = max(DUPEK[4][j-2], DUPEK[5][j]+POT[4][j-2]);
           //         if (j+2 < k) DUPEK[6][j+1] = max(DUPEK[4][j], DUPEK[4][j+2]);
           //         DUPEK[6][j-1] = max(DUPEK[4][j-2], DUPEK[4][j]);
                }
            }

            DUPEK[5][j] += POT[5][j];

        }

//        for (int j = 0; j < 6; j++) {
//            for (int l = 0; l < k; l++) {
//                cout << DUPEK[j][l] << " ";
//            }
//            cout << "\n";
//        }

//        cout << "= = = = = = = =\n";


        for (int j = 0; j < k; j++) {
            for (int l = 0; l < 8; l++) {
                DUPEK[l][j] = DUPEK[l+1][j];
                POT[l][j] = POT[l+1][j];
            }
        }
    }


    ll ret = 0;
    for (int i = 0; i < k; i++) {
        if (ret < DUPEK[4][i]) ret = DUPEK[4][i];
    }

    cout << ret << "\n";

    return 0;
}






