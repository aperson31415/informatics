#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;

    vector<long long> s(N + 1, 0);
    vector<long long> S(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        cin >> s[i];
        S[i] = S[i - 1] + s[i];
    }

    int K; cin >> K;
    
    vector<long long> p(K);
    for (int i = 0; i < K; ++i) {
        cin >> p[i];
    }

    // dp[i] := does a valid partition exist ending at index i
    vector<bool> dp(N + 1, false);
    vector<int> parent(N + 1, -1);
    dp[0] = true;

    vector<unordered_map<long long, int>> best_j(K);

    // Base case
    for (int k = 0; k < K; ++k) {
        long long val = S[0] - 0 * p[k]; // 0
        best_j[k][val] = 0;
    }

    // Transitions
    for (int i = 1; i <= N; ++i) {
        for (int k = 0; k < K; ++k) {
            long long val = S[i] - (long long)i * p[k];
            if (best_j[k].count(val)) {
                dp[i] = true;
                parent[i] = best_j[k][val];
                break;
            }
        }

        // Future lookups
        if (dp[i]) {
            for (int k = 0; k < K; ++k) {
                long long val = S[i] - (long long)i * p[k];
                if (best_j[k].find(val) == best_j[k].end()) {
                    best_j[k][val] = i;
                }
            }
        }
    }

    if (!dp[N]) {
        cout << "IMPOSSIBLE";
        return 0;
    }

    vector<pair<int, int>> ranges;
    int curr = N;
    while (curr > 0) {
        int prev = parent[curr];
        ranges.push_back({prev + 1, curr});
        curr = prev;
    }

    cout << "POSSIBLE\n";
    cout << ranges.size() << "\n";

    for (int i = (int)ranges.size() - 1; i >= 0; --i) {
        cout << ranges[i].first << " " << ranges[i].second << "\n";
    }
}
