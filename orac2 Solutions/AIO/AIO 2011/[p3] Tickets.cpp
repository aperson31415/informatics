#include <bits/extc++.h>
using namespace std;
#define int long long

const long long INF = 1e18;

signed main() {
    int c1, d1, c2, d2, D; cin >> c1 >> d1 >> c2 >> d2 >> D;

    vector<int> a(D + 1, 0);
    for (int i = 1; i <= D; ++i) cin >> a[i];

    vector<int> dp(D + 1, INF);
    dp[0] = 0;

    // Min-heaps storing pairs of {dp[j], j}
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> heap1, heap2;

    for (int i = 1; i <= D; ++i) {
        if (dp[i - 1] != INF) {
            heap1.push({dp[i - 1], i - 1});
            heap2.push({dp[i - 1], i - 1});
        }

        // Ticket 1 validity range check via lower_bound
        int target1 = a[i] - d1 + 1;
        auto it1 = lower_bound(a.begin() + 1, a.begin() + i + 1, target1);
        int min_j1 = distance(a.begin(), it1) - 1;

        while (!heap1.empty() && heap1.top().second < min_j1) heap1.pop();

        // Ticket 2 validity range check via lower_bound
        int target2 = a[i] - d2 + 1;
        auto it2 = lower_bound(a.begin() + 1, a.begin() + i + 1, target2);
        int min_j2 = distance(a.begin(), it2) - 1;

        while (!heap2.empty() && heap2.top().second < min_j2) heap2.pop();

        int opt1 = heap1.empty() ? INF : heap1.top().first + c1;
        int opt2 = heap2.empty() ? INF : heap2.top().first + c2;

        dp[i] = min(opt1, opt2);
    }

    cout << dp[D];
}
