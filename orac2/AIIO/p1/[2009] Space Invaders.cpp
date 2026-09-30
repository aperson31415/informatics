#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4")
 
signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);
 
    freopen("spacein.txt", "r", stdin);
    freopen("spaceout.txt", "w", stdout);
 
    int w, h; cin >> w >> h;
    int k; cin >> k;
 
    // Bad ranges
    vector<pair<int, int>> intervals;
    for(int i = 0; i < k; i++) {
        int minw = INT_MAX, maxw = INT_MIN;
        int p; cin >> p;
        for(int j = 0; j < p; j++) {
            int x, y;
            cin >> x >> y;
            minw = min(minw, x);
            maxw = max(maxw, x);
        }
        intervals.push_back({minw, maxw});
    }
 
    // Sort for greedy merging later
    sort(intervals.begin(), intervals.end());
 
    long long badcnt = 0;
    if (!intervals.empty()) {
        // Merge
        int current_start = intervals[0].first;
        int current_end = intervals[0].second;
 
        for (size_t i = 1; i < intervals.size(); i++) {
            if (intervals[i].first <= current_end) {
                // Extend the end
                current_end = max(current_end, intervals[i].second);
            } else {
                // Gap
                badcnt += (current_end - current_start);
                current_start = intervals[i].first;
                current_end = intervals[i].second;
            }
        }
        // Last interval!
        badcnt += (current_end - current_start);
    }
 
    cout << (long long)w - badcnt << "\n";
}