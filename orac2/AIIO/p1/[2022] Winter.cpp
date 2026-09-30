#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<bool> visited, nulled;
vector<int> dp, p;
vector<vector<int>> adj;

void dfs(int node) {
  visited[node] = true;
  for(int u : adj[node]) {
    if(!visited[u]) {
      dfs(u);
      nulled[node] = false;
    }
  }
  dp[node] = p[node];
  if(!nulled[node]) {
    for(int u : adj[node]) {
      if(dp[u] >= 0) {
        dp[node] += dp[u];
      }
    }
  }
}

signed main() {
  int n; cin >> n;
  visited.resize(n, false);
  dp.resize(n, 0);
  nulled.resize(n, true);
  p.resize(n);
  for(int i = 0; i < n; i++) cin >> p[i];
  adj.resize(n);
  for(int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs(0);
  int res = 0;
  res = dp[0];
  for(auto elem : dp) {
    res = max(res, elem);
  }
  cout << res;
}
