#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int N, K; cin >> N >> K;
 
    vector<int> H(N);
    for (int i = 0; i < N; i++) cin >> H[i];
 
    long long ans = 0;
 
    int L = H[0], R = H[0];
 
    // Cost
    for (int i = 0; i < K; i++) {
        L = min(L, H[i]);
        R = max(R, H[i]);
 
        if (i > 0) ans += abs(H[i] - H[i - 1]);
    }
 
    int a = min(H[0], H[K - 1]);
    int b = max(H[0], H[K - 1]);
 
    int x = INT_MAX, y = INT_MIN;
 
    // Minimum and maximum heights of other guests
    for (int i = K; i < N; i++) {
        x = min(x, H[i]);
        y = max(y, H[i]);
    }
 
    if (x != INT_MAX) {
        if (x < L) ans += min(a - x, 2 * (L - x));
        if (y > R) ans += min(y - b, 2 * (y - R));
    }
 
    cout << ans;
}
