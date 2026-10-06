#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N; cin >> N;
    vector<int> k(N);
    for(int i = 0; i < N; i++) cin >> k[i];

    set<int> ends;
    ends.insert(k[0]);
    int res = 1;

    for(int i = 1; i < N; i++) {
        if(k[i] > *(ends.rbegin())) {
            res++;
            ends.insert(k[i]);
        } else {
            ends.erase(ends.upper_bound(k[i]));
            ends.insert(k[i]);
        }
    }

    cout << res;
}