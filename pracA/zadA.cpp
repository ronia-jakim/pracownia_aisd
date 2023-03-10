#include<iostream>
#include<bits/stdc++.h>

using namespace std;

#define ll long long int
#define M 1000001

int main () {
    ll n;
    vector<ll> dst;
    ll total = 0;
    cin >> n;

    if (n <= 1) {
        cout << 0 << endl;
        return 0;
    }

    for (ll i = 0; i < n; i++) {
        ll pom;
        cin >> pom;
        total += pom;
        dst.push_back(pom);
    }

    // if (n == 2) {
    //     cout << min(dst[0], dst[1]) << endl;
    //     return 0;
    // }

    ll left = 0;
    ll right = 0;

    ll traveled = dst[0];
    ll ret = traveled;

    while (right < n) {
        // robie nowy krok
        right++;
        // jezeli ten krok nie przebil mnie przez total/2, czyli odpowiada za dlugosc sciezki
        if (traveled + dst[right] < total/2) {
            traveled += dst[right];
            if (ret < min(traveled, total-traveled)) {
                ret = min(traveled, total-traveled);
                cout << ret << " " << traveled << " " << right << " " << left << "dd\n";
            }
        }
        else {
            // jezeli dostaje dluzsza droge po zrobieniu go ale zaczynajac od wierzcholka bardziej na prawo
            ll pom = traveled + dst[right] - dst[left];
            if (pom < total/2 && pom > traveled) {
                traveled = pom;
                left++;
                if (ret < min(traveled, total-traveled)) {
                    ret = min(traveled, total-traveled);
                    cout << ret << "ddd\n";
                }
            }
            else {
                // juz bardziej wydluzyc sie nie da, chyba, ze przekraczajac total/2
                cout << traveled << " " << total-((traveled)+dst[right]) << " pp " << total-pom << " " << total << endl;

                // potencjalna odpowiedz to traveled lub total-(traveled+dst[right])
                //ret = min(traveled, total - (traveled+dst[right]));
                ret = max(min(traveled, total - traveled), min(total - (traveled+dst[right]), traveled+dst[right]));

                //podwijam spodnice sciezki?
                traveled += dst[right];
                while(traveled > total/2) {
                    traveled -= dst[left];
                    left++;
                }
                cout << left << " " << right << " ll " << ret << endl;
            }
        }
    }
    cout << ret << endl;
    return 0;
}