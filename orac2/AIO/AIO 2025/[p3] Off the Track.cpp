#include <bits/stdc++.h>
using namespace std;
 
signed main() noexcept {
    int N, L;
    cin >> N >> L;
    vector<int> P(N);
    for(int i = 0; i < N; i++) cin >> P[i];
    int ans = P[P.size() - 1];
    if(L - P[0] < ans) {
        ans = L - P[0];
    }
 
    for(int i = 0; i < N - 1; i++) {
        int t = 2* P[i] + L - P[i + 1];
        if(t < ans) ans = t;
    }
 
    for(int i = 1; i < N; i++) {
        int t = 2* (L - P[i]) + P[i - 1];
        if(t < ans) ans = t;
    }
 
    cout << ans;
}
