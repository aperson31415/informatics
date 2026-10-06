#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int l; cin >> l;
    vector<vector<int>> matrix(l, vector<int>(3));
    for(int i = 0; i < l; i++) cin >> matrix[i][0] >> matrix[i][1] >> matrix[i][2];

    vector<int> dp(l);
    dp[0] = 0;
    dp[1] = max({0, matrix[0][0] + matrix[0][1] + matrix[1][0] + matrix[1][1], matrix[0][1] + matrix[1][1] + matrix[0][2] + matrix[1][2]});

    int max_before = max(dp[0], dp[1]);
    int max_before2 = 0;

    for(int i = 2; i < l; i++) {
        dp[i] = max({max_before, max_before2 + matrix[i - 1][0] + matrix[i][0] + matrix[i - 1][1] + matrix[i][1], max_before2 + matrix[i - 1][1] + matrix[i][1] + matrix[i - 1][2] + matrix[i][2]});
        max_before = max(max_before, dp[i]);
        max_before2 = max(max_before2, dp[i - 1]);
    }

    cout << dp[l - 1];
}