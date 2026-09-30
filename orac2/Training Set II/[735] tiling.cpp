#include <bits/stdc++.h>
using namespace std;
 
int main() {
    long long n, m, k;
    cin >> n >> m >> k;
 
    long long M = 1LL << m;                 // number of masks (2^m)
    vector<long long> dp(M, 0), next_dp(M, 0);
 
    dp[0] = 1;                              // no boards placed yet
 
    for (long long pos = 0; pos < n; ++pos) {
        fill(next_dp.begin(), next_dp.end(), 0);
 
        for (long long mask = 0; mask < M; ++mask) {
            long long ways = dp[mask];
            if (!ways) continue;
 
            // Try placing 0 (wood) and 1 (iron)
            for (long long bit = 0; bit <= 1; ++bit) {
                long long newMask = ((mask << 1) & (M - 1)) | bit;
 
                // Once we have at least m boards, enforce the constraint
                if (pos + 1 >= m) {
                    long long ones = __builtin_popcountll(newMask);
                    if (ones < k) continue;
                }
 
                next_dp[newMask] += ways;
            }
        }
 
        dp.swap(next_dp);
    }
 
    long long ans = 0;
    for (long long mask = 0; mask < M; ++mask)
        ans += dp[mask];
 
    cout << ans << "\n";
}
