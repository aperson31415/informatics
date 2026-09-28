#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int main() {
    int n, c; cin >> n >> c;

    vector<int> x(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
    }

    int p; cin >> p;
    vector<vector<int>> adj(c + 1);
    vector<int> deg(c + 1, 0);

    for(int i = 0; i < p; ++i) {
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
      deg[u]++;
      if(u != v) {
        adj[v].push_back(u);
        deg[v]++;
      }
    }

    int B = max(1, (int)sqrt(2 * p));

    vector<bool> is_heavy(c + 1, false);
    vector<int> heavy_id(c + 1, -1);
    int heavy_count = 0;

    for(int i = 1; i <= c; ++i) {
        if(deg[i] >= B) {
            is_heavy[i] = true;
            heavy_id[i] = heavy_count++;
        }
    }

    // Separate neighbors into light and heavy for each color
    vector<vector<int>> light_neighbors(c + 1);
    vector<vector<int>> heavy_neighbors(c + 1);

    for (int u = 1; u <= c; ++u) {
        for (int v : adj[u]) {
            if (is_heavy[v]) {
                heavy_neighbors[u].push_back(v);
            } else {
                light_neighbors[u].push_back(v);
            }
        }
    }

    vector<long long> dp(n + 1, 0);
    dp[1] = 1;

    vector<long long> light_sum(c + 1, 0);
    vector<long long> heavy_sum(heavy_count, 0);
    vector<long long> sum_light_compatible_with(heavy_count, 0);

    // Initialize tile 1
    int c1 = x[1];
    if (dp[1] > 0) {
        if (!is_heavy[c1]) {
            light_sum[c1] = (light_sum[c1] + dp[1]) % MOD;
            for (int h_nbr : heavy_neighbors[c1]) {
                sum_light_compatible_with[heavy_id[h_nbr]] = (sum_light_compatible_with[heavy_id[h_nbr]] + dp[1]) % MOD;
            }
        } else {
            heavy_sum[heavy_id[c1]] = (heavy_sum[heavy_id[c1]] + dp[1]) % MOD;
        }
    }

    for (int i = 2; i <= n; ++i) {
        int cur_col = x[i];
        long long ways = 0;

        if (!is_heavy[cur_col]) {
            // Sum from light neighbors
            for (int l_nbr : light_neighbors[cur_col]) {
                ways = (ways + light_sum[l_nbr]) % MOD;
            }
            // Sum from heavy neighbors
            for (int h_nbr : heavy_neighbors[cur_col]) {
                ways = (ways + heavy_sum[heavy_id[h_nbr]]) % MOD;
            }
        } else {
            // Sum from light compatible colors O(1)
            ways = sum_light_compatible_with[heavy_id[cur_col]];
            // Sum from heavy neighbors
            for (int h_nbr : heavy_neighbors[cur_col]) {
                ways = (ways + heavy_sum[heavy_id[h_nbr]]) % MOD;
            }
        }

        dp[i] = ways;

        if (dp[i] > 0) {
            if (!is_heavy[cur_col]) {
                light_sum[cur_col] = (light_sum[cur_col] + dp[i]) % MOD;
                for (int h_nbr : heavy_neighbors[cur_col]) {
                    sum_light_compatible_with[heavy_id[h_nbr]] = (sum_light_compatible_with[heavy_id[h_nbr]] + dp[i]) % MOD;
                }
            } else {
                heavy_sum[heavy_id[cur_col]] = (heavy_sum[heavy_id[cur_col]] + dp[i]) % MOD;
            }
        }
    }

    cout << dp[n];
}
