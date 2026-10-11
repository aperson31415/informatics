#include <bits/stdc++.h>
using namespace std;
#define int long long
 
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
 
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
 
    int s; cin >> s;
 
    vector<pair<int, int>> games(s);
    for(int i = 0; i < s; i++) cin >> games[i].first >> games[i].second;
 
    vector<int> X(2*n + 1, 0);
    for(int i = 0; i < n; i++) X[a[i]]++;
    for(int i = 1; i <= 2*n; i++) {
        X[i] += X[i-1];
    }
 
    vector<int> lowerthanme(n);
    for(int i = 0; i < n; i++) {
        lowerthanme[i] = n - X[b[i]];
    }
 
    vector<int> pref_lo(n + 1, 0);
    for(int i = 0; i < n; i++) {
        pref_lo[i+1] = pref_lo[i] + lowerthanme[i];
    }
 
    // queries
    for(auto [ai, bj] : games) {
        auto it = lower_bound(lowerthanme.begin(), lowerthanme.begin() + bj, ai);
        int dist = it - lowerthanme.begin();
 
        int scoreA = pref_lo[dist] + (bj - dist) * ai;
        int scoreB = ai * bj - scoreA;
 
        cout << scoreA << ' ' << scoreB << '\n';
    }
}
