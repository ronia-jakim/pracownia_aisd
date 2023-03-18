#include<iostream>
#include<bits/stdc++.h>

using namespace std;

#define ll long long int
#define M 1000001

int main () {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

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

    ll traveled = 0;//dst[0];
    ll ret = traveled;

    while (left < n-1) {
        //dopóki mi to poprawia sytuację, to robię krok:
        while (min(traveled, total-traveled) < min(traveled+dst[right], total-traveled-dst[right])) {
            traveled += dst[right];
            right++;
        }
        ret = max(ret, min(traveled, total-traveled));
        traveled -= dst[left];
        left++;
    }
    
    cout << ret << "\n";
    return 0;
}
