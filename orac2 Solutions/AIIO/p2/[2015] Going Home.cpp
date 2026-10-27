#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const long long INF = 1e18;

struct Edge {
  int to;
  long long weight;
};

vector<long long> dijkstra(int start, int N, const vector<vector<Edge>> &adj) {
  vector<long long> dist(N + 1, INF);
  priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                 greater<pair<long long, int>>>
      pq;

  dist[start] = 0;
  pq.push({0, start});

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (d > dist[u])
      continue;

    for (const auto &edge : adj[u]) {
      if (dist[u] + edge.weight < dist[edge.to]) {
        dist[edge.to] = dist[u] + edge.weight;
        pq.push({dist[edge.to], edge.to});
      }
    }
  }
  return dist;
}

int main() {
  int N, M;
  cin >> N >> M;

  vector<vector<Edge>> adj(N + 1);
  for (int i = 0; i < M; ++i) {
    int u, v;
    long long w;
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  // Run Dijkstra from Vlad and Tony
  vector<long long> dist1 = dijkstra(1, N, adj);
  vector<long long> dist2 = dijkstra(2, N, adj);

  vector<int> nodes(N);
  for (int i = 1; i <= N; ++i)
    nodes[i - 1] = i;

  // Get number of shortest paths from 1
  sort(nodes.begin(), nodes.end(),
       [&](int a, int b) { return dist1[a] < dist1[b]; });
  vector<long long> ways1(N + 1, 0);
  ways1[1] = 1;
  for (int u : nodes) {
    if (dist1[u] == INF)
      continue;
    for (const auto &edge : adj[u]) {
      int v = edge.to;
      if (dist1[v] == dist1[u] + edge.weight) {
        ways1[v] = (ways1[v] + ways1[u]) % MOD;
      }
    }
  }

  // Get number of shortest paths from 2
  sort(nodes.begin(), nodes.end(),
       [&](int a, int b) { return dist2[a] < dist2[b]; });
  vector<long long> ways2(N + 1, 0);
  ways2[2] = 1;
  for (int u : nodes) {
    if (dist2[u] == INF)
      continue;
    for (const auto &edge : adj[u]) {
      int v = edge.to;
      if (dist2[v] == dist2[u] + edge.weight) {
        ways2[v] = (ways2[v] + ways2[u]) % MOD;
      }
    }
  }

  if (dist1[N] == INF || dist2[N] == INF || dist1[N] != dist2[N]) {
    long long default_ways =
        (ways1[N] == INF || ways2[N] == INF) ? 0 : (ways1[N] * ways2[N]) % MOD;
    cout << 0 << "\n" << default_ways << "\n";
    return 0;
  }

  // dist1[u] == dist2[u]
  vector<int> sync_nodes;
  for (int i = 1; i <= N; ++i) {
    if (dist1[i] != INF && dist1[i] == dist2[i]) {
      sync_nodes.push_back(i);
    }
  }

  sort(sync_nodes.begin(), sync_nodes.end(), [&](int a, int b) {
    if (dist1[a] != dist1[b])
      return dist1[a] < dist1[b];
    return a < b;
  });

  // do dp
  vector<long long> max_qt(N + 1, -1);
  vector<long long> dp_ways(N + 1, 0);

  // bases
  for (int u : sync_nodes) {
    max_qt[u] = 0;
    dp_ways[u] = (ways1[u] * ways2[u]) % MOD;
  }

  // transitions
  for (int u : sync_nodes) {
    if (max_qt[u] == -1)
      continue;

    for (const auto &edge : adj[u]) {
      int v = edge.to;
      // shared edge
      if (dist1[v] != INF && dist1[v] == dist2[v]) {
        if (dist1[v] == dist1[u] + edge.weight &&
            dist2[v] == dist2[u] + edge.weight) {
          long long new_qt = max_qt[u] + edge.weight;
          long long new_ways = dp_ways[u];

          if (new_qt > max_qt[v]) {
            max_qt[v] = new_qt;
            dp_ways[v] = new_ways;
          } else if (new_qt == max_qt[v]) {
            dp_ways[v] = (dp_ways[v] + new_ways) % MOD;
          }
        }
      }
    }
  }

  long long ans_qt = max_qt[N] == -1 ? 0 : max_qt[N];
  long long ans_ways = dp_ways[N];

  if (ans_qt == 0 && ans_ways == 0) {
    ans_ways = (ways1[N] * ways2[N]) % MOD;
  }

  cout << ans_qt << "\n";
  cout << ans_ways << "\n";
}
