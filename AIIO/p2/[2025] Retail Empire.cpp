#include <bits/stdc++.h>
using namespace std;

signed main() {
    int N, A, K; cin >> N >> A >> K;
    vector<int> cost(N), profit(N);
    for(int i = 0; i < N; i++) cin >> cost[i] >> profit[i];

    vector<int> dp(K + 1, 0);

    for (int i = 0; i < N; i++) {
        for (int w = K; w >= cost[i]; w--) {
            dp[w] = max(dp[w], dp[w - cost[i]] + profit[i]);
        }
    }

    // i hope this works
    
    int days = 0, money = A;
    while(true) {
        days++;

        money += dp[money];
        if(money >= K) {
            cout << days + 1;
            return 0;
        }
    }
    
}