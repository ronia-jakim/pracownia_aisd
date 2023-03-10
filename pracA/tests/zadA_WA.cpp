#include<iostream>
#include<bits/stdc++.h>

using namespace std;

#define ll long long int
#define M 1000001

//ll total_len;

int main () {
    ll n;
    vector<vector<ll>> dist;
    cin >> n;

    ll total_len = 0;

    dist.push_back({{0}});

    for (ll i = 1; i <= n-1; i++) {
        ll pom;
        cin >> pom;
        total_len += pom;

        dist.push_back({{total_len}});

        for (ll j = 1; j <= i; j++) {
            dist[i].push_back({total_len-dist[j][0]});
        }
    }

    ll dst_lst_fst;
    cin >> dst_lst_fst;

    total_len += dst_lst_fst;

    ll ret = 0;

    if (dst_lst_fst < dist[n-1][0]) dist[n-1][0] = dst_lst_fst;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < i; j++) {
            ll min_dst = min(dist[i][j], total_len - dist[i][j]);

            if (ret < min_dst) ret = min_dst;
        }
    }
    cout << ret << endl;

    return 0;
}