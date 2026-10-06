#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    unordered_map<int, int> pos; // Map leaflet position value to its index
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }

    if (n <= 0) {
        cout << 0;
        return 0;
    }

    vector<vector<int>> d(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(a[j] >= a[i]) continue;
            d[i].push_back(a[i] - a[j]);
        }
    }

    map<pair<int, int>, int> dp;
    int res = min(n, 1); // Minimum possible length is 1 (or 2 if n >= 2)

    for(int i = 0; i < n; i++) {
        for(int dist : d[i]) {
            int prev_val = a[i] - dist;
            int prev_idx = pos[prev_val]; // Find the actual index of the previous element

            if(dp.count({prev_idx, dist})) {
                dp[{i, dist}] = dp[{prev_idx, dist}] + 1;
            } else {
                dp[{i, dist}] = 2;
            }
            
            res = max(res, dp[{i, dist}]);
        }
    }

    cout << res;
}
