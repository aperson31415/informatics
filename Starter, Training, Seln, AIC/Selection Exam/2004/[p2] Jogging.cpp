#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;
#define fio(in, out) freopen(in, "r", stdin); freopen(out, "w", stdout)

struct Edge {
    int to;
    int weight;
};

int main() {
    fio("jogin.txt", "jogout.txt");
    cin.tie(0)->sync_with_stdio(0);

    int L; cin >> L;

    vector<vector<Edge>> adj(L + 1);
    vector<int> in_degree(L + 1, 0);
    
    int u, v, e;
    while (cin >> u >> v >> e && (u != 0 || v != 0 || e != 0)) {
        adj[u].push_back({v, e});
        in_degree[v]++;
    }

    vector<long long> dp(L + 1, 0);
    queue<int> q;

    for (int i = 1; i <= L; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    long long max_benefit = 0;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        max_benefit = max(max_benefit, dp[curr]);

        for (auto& edge : adj[curr]) {
            dp[edge.to] = max(dp[edge.to], dp[curr] + edge.weight);

            in_degree[edge.to]--;
            if (in_degree[edge.to] == 0) {
                q.push(edge.to);
            }
        }
    }

    for (int i = 1; i <= L; ++i) {
        max_benefit = max(max_benefit, dp[i]);
    }

    cout << max_benefit << endl;

    return 0;
}