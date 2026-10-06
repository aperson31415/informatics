#include <bits/stdc++.h>
using namespace std;

struct edge {int node, weight;};

int n, res;
vector<vector<edge>> adj, adj_rev;
vector<int> height, dp;
vector<bool> visitedh, visitedp, visitedg;
vector<bool> istop;

void dfs_height(int node) {
  visitedh[node] = true;
  for(auto [u, weight] : adj[node]) {
    if(visitedh[u]) continue;
    height[u] = height[node] + weight;
    dfs_height(u);
  }
}

void dfs_dp(int node) {
  visitedp[node] = true;
  // children
  for(auto [u, weight] : adj[node]) {
    if(visitedp[u]) continue;
    dfs_dp(u);
  }

  // dp
  if((int)adj[node].size() != 0) {
    for(auto [u, weight] : adj[node]) {
      if(dp[node] == -1) dp[node] == dp[u];
      else dp[node] = min(dp[node], dp[u]);
    }
  }
}

void dfs_greed(int node, int taken_alr) {
  visitedg[node] = true;
  // greedily choose stuff
  res += dp[node] - taken_alr;
  // dfs
  for(auto [u, weight] : adj[node]) {
    if(visitedg[u]) continue;
    dfs_greed(u, dp[node]);
  }
}

int main() {
  cin >> n;
  adj.resize(n); adj_rev.resize(n);
  height.resize(n, -1); dp.resize(n, INT_MAX);
  visitedh.resize(n, false); visitedp.resize(n, false); visitedg.resize(n, false);
  istop.resize(n, false);

  for(int i = 0; i < n; i++) {
    int a, x, b, y; cin >> a >> x >> b >> y;
    if(a == 0 and b == 0 and x == 0 and y == 0) {
      istop[i] = true;
      continue;
    }
    a--; b--;

    adj[i].push_back({a, x});
    adj[i].push_back({b, y});

    adj_rev[a].push_back({i, x});
    adj_rev[b].push_back({i, y});
  }

  // get heights
  height[0] = 0;
  dfs_height(0);
  // dp bases
  int max_height = 0;
  for(int i = 0; i < n; i++) max_height = max(max_height, height[i]);
  for(int i = 0; i < n; i++) {
    if(!istop[i]) continue;
    dp[i] = max_height - height[i];
  }
  // dp transitions
  dfs_dp(0);
  // greedily choose stuff
  res = 0;
  dfs_greed(0, 0);

  // output
  cout << res;
}
