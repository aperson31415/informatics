#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;
 
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
 
    freopen("taxiin.txt", "r", stdin);
    freopen("taxiout.txt", "w", stdout);
 
    int s, n; cin >> s >> n;
    vector<int> seats(n * 2), costs(n * 2);
    for(int i = 0; i < n; i++) {
        cin >> costs[i * 2] >> seats[i * 2];
        costs[i * 2 + 1] = costs[i * 2];
 
        if(seats[i * 2] != 1) seats[i * 2 + 1] = seats[i * 2] - 1;
        else seats[i * 2 + 1] = seats[i * 2];
    }
 
    vector<int> dp(s + 1, -1);
    dp[0] = 0;
 
    for(int i = 0; i <= s; i++) {
        for(int j = 0; j < n*2; j++) {
            if (i - seats[j] >= 0) {
                //cout << j << " ";
                if(dp[i] == -1 and dp[i - seats[j]] != -1) {
                    dp[i] = dp[i - seats[j]] + costs[j];
                } else if(dp[i] != -1 and dp[i - seats[j]] != -1) {
                    dp[i] = min(dp[i], dp[i - seats[j]] + costs[j]);
                }
            }
        }
        //cout << dp[i] << "\n";
    }
 
    cout << dp[s];
}