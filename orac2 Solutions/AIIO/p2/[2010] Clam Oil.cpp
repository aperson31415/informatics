#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("clamin.txt","r",stdin); freopen("clamout.txt", "w",stdout);

    int N, C;
    cin >> N >> C;

    vector<long long> profit(N + 1), complaints(N + 1);

    for (int i = 1; i <= N; i++) {
        long long p, c;
        int parent = 0;

        if (i == 1) {
            cin >> p >> c;
        } else {
            cin >> p >> c >> parent;
        }

        if (i == 1) {
            profit[i] = p;
            complaints[i] = c;
        } else {
            profit[i] = profit[parent] + p;
            complaints[i] = complaints[parent] + c;
        }
    }

    vector<long long> dp(C + 1, 0);

    for (int i = 1; i <= N; i++) {
        long long w = complaints[i];
        long long v = profit[i];

        if (w > C) continue;

        for (int b = (int)w; b <= C; b++) {
            dp[b] = max(dp[b], dp[b - (int)w] + v);
        }
    }

    cout << dp[C] << '\n';

    return 0;
}
