#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;
  cin >> N >> M;

  vector<vector<int>> adj(N + 1);
  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int K;
  cin >> K;
  vector<int> A(K + 1);
  for (int i = 1; i <= K; ++i) {
    cin >> A[i];
  }

  int Q;
  cin >> Q;
  vector<int> B(Q + 1);
  // queries[j] := {query_index, starting_room} for games starting at step j
  vector<vector<pair<int, int>>> queries(K + 1);
  for (int i = 1; i <= Q; ++i) {
    cin >> B[i];
    queries[i].push_back({i, B[i]});
  }

  // dp[u] := max points from the current step onwards if Bruno is in room u
  vector<int> dp(N + 1, 0); // At step K, 0 points remaining
  vector<int> ans(Q + 1, 0);

  // Process backwards from step K-1 down to 1
  for (int j = K - 1; j >= 1; --j) {
    vector<int> next_dp(N + 1, 0);
    for (int u = 1; u <= N; ++u) {
      // Option 1: Stay still (v = u)
      int val = dp[u];
      if (u == A[j + 1]) {
        val += 1; // Earn a point if Amy steps into this room
      }
      next_dp[u] = val;

      // Move to an adjacent neighbor v
      for (int v : adj[u]) {
        next_dp[u] = max(next_dp[u], dp[v]);
      }
    }
    dp = next_dp;

    for (auto &q : queries[j]) {
      int q_idx = q.first;
      int room = q.second;
      ans[q_idx] = dp[room];
    }
  }

  for (int i = 1; i <= Q; ++i) {
    cout << ans[i] << "\n";
  }
}
