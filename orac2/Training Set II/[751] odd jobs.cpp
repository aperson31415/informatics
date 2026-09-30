#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
int main() {
    ll N; cin >> N;
    vector<vector<ll>> matrix(N, vector<ll>(N));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> matrix[i][j];
        }
    }
    vector<ll> dp(1 << N, LLONG_MAX); 
    /*i          := bitmask of jobs that have been used
    dp[i]        := min cost*/
 
    dp[0] = 0;
 
    for(ll i = 0; i < (1 << N); i++) {
        if (dp[i] == LLONG_MAX) continue;
        // Iterate through bitmasks
        for(ll job = 0; job < N; job++) {
            // Iterate through new jobs to add
            if(!((i >> job) & 1)) {
                // Job not set, try setting
                ll newMask = i | (1LL << job);
                ll intern = __builtin_popcountll(i);
                dp[newMask] = min(dp[newMask], dp[i] + matrix[intern][job]);
            }
        }
        //cout << "at bitmask " << i << ", the minimum mistakes is " << dp[i] << endl;
    }
 
    cout << dp[(1 << N) - 1];
}
