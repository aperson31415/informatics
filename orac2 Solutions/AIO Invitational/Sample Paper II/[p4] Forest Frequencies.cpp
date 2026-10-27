#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  scanf("%d", &n);
  vector<int> x(n + 2), pos(n + 2, 0);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &x[i]);
    pos[x[i]] = i;
  }

  vector<vector<int>> g(n + 1);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  if (n == 1)
    return 0;

  const int LOG = 18;
  vector<int> par(n + 1, 0), dep(n + 1, 0);
  vector<vector<int>> up(LOG, vector<int>(n + 1, 0));
  {
    vector<int> q;
    q.reserve(n);
    q.push_back(1);
    par[1] = 1;
    vector<char> vis(n + 1, 0);
    vis[1] = 1;
    for (size_t h = 0; h < q.size(); h++) {
      int u = q[h];
      for (int v : g[u]) {
        if (!vis[v]) {
          vis[v] = 1;
          par[v] = u;
          dep[v] = dep[u] + 1;
          q.push_back(v);
        }
      }
    }
  }
  for (int v = 1; v <= n; v++)
    up[0][v] = par[v]; // root's parent is itself
  for (int j = 1; j < LOG; j++)
    for (int v = 1; v <= n; v++)
      up[j][v] = up[j - 1][up[j - 1][v]];

  auto lca = [&](int a, int b) {
    if (dep[a] < dep[b])
      swap(a, b);
    int diff = dep[a] - dep[b];
    for (int j = 0; j < LOG; j++)
      if (diff >> j & 1)
        a = up[j][a];
    if (a == b)
      return a;
    for (int j = LOG - 1; j >= 0; j--) {
      if (up[j][a] != up[j][b]) {
        a = up[j][a];
        b = up[j][b];
      }
    }
    return up[0][a];
  };

  vector<vector<int>> adj(n + 1);
  for (int v = 1; v < n; v++) {
    int a = pos[v], b = pos[v + 1];
    int c = lca(a, b);
    adj[c].push_back(a);
    adj[c].push_back(b);
  }

  // 0-1 BFS from node 1
  const int INF = INT_MAX;
  vector<int> dist(n + 1, INF);
  deque<int> dq;
  dist[1] = 0;
  dq.push_back(1);

  while (!dq.empty()) {
    int u = dq.front();
    dq.pop_front();

    // free move up to parent
    if (u != 1 && dist[par[u]] > dist[u]) {
      dist[par[u]] = dist[u];
      dq.push_front(par[u]);
    }

    for (int w : adj[u]) {
      if (dist[w] > dist[u] + 1) {
        dist[w] = dist[u] + 1;
        dq.push_back(w);
      }
    }
  }

  for (int k = 2; k <= n; k++)
    printf("%d\n", dist[k]);
}
