#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int to;
  long long weight;
};

struct ChildInfo {
  int id;
  long long S;
  long long T;
  long long h;
  long long ret_val;
  long long no_ret_val;
  long long max_d;
};

int n;
vector<long long> P;
vector<vector<Edge>> adj;
vector<long long> S;
vector<long long> W;
vector<long long> ret_cost;
vector<long long> no_ret_cost;
vector<long long> max_down;

bool compare_children(const ChildInfo &a, const ChildInfo &b) {
  return a.S * b.T > b.S * a.T;
}

void dfs(int u, int p) {
  S[u] = P[u];
  W[u] = 0;
  vector<ChildInfo> children;

  for (const auto &edge : adj[u]) {
    int v = edge.to;
    long long h = edge.weight;
    if (v == p)
      continue;
    dfs(v, u);
    S[u] += S[v];
    W[u] += W[v] + h;
    long long T = 2 * h + 2 * W[v];
    children.push_back(
        {v, S[v], T, h, ret_cost[v], no_ret_cost[v], max_down[v]});
  }

  if (children.empty()) {
    ret_cost[u] = 0;
    no_ret_cost[u] = 0;
    max_down[u] = 0;
    return;
  }

  sort(children.begin(), children.end(), compare_children);

  int k = children.size();
  vector<long long> suffix_S(k + 1, 0);
  for (int i = k - 1; i >= 0; --i) {
    suffix_S[i] = suffix_S[i + 1] + children[i].S;
  }

  long long current_ret = 0;
  for (int i = 0; i < k; ++i) {
    long long sum_after = suffix_S[i + 1];
    current_ret += children[i].h * children[i].S + children[i].ret_val +
                   children[i].T * sum_after;
  }
  ret_cost[u] = current_ret;

  max_down[u] = children[k - 1].h + children[k - 1].max_d;

  no_ret_cost[u] =
      ret_cost[u] - children[k - 1].ret_val + children[k - 1].no_ret_val;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n;

  P.resize(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> P[i];
  }

  adj.resize(n + 1);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    long long h;
    cin >> u >> v >> h;
    adj[u].push_back({v, h});
    adj[v].push_back({u, h});
  }

  S.resize(n + 1, 0);
  W.resize(n + 1, 0);
  ret_cost.resize(n + 1, 0);
  no_ret_cost.resize(n + 1, 0);
  max_down.resize(n + 1, 0);

  dfs(1, 0);

  cout << no_ret_cost[1];
}
