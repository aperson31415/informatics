#include "nav.h"
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

static int subtask_id;
static int n_vert, m_edge;
static vector<vector<int>> adj;
static vector<pair<int, int>> edges_list;
static vector<vector<int>> dist_matrix;

static vector<int> tree_sz;
static vector<int> tree_parent;
static vector<int> tree_vis;
static int tree_token = 0;

void init(int subtask, int n, int m, std::vector<int> A, std::vector<int> B) {
  subtask_id = subtask;
  n_vert = n;
  m_edge = m;

  edges_list.resize(m);
  adj.assign(n, vector<int>());
  for (int i = 0; i < m; ++i) {
    edges_list[i] = {A[i], B[i]};
    adj[A[i]].push_back(B[i]);
    adj[B[i]].push_back(A[i]);
  }

  if (subtask == 1 || subtask == 4) {
    dist_matrix.assign(n, vector<int>(n, 1e9));
    for (int i = 0; i < n; ++i) {
      dist_matrix[i][i] = 0;
      queue<int> q;
      q.push(i);
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
          if (dist_matrix[i][v] > dist_matrix[i][u] + 1) {
            dist_matrix[i][v] = dist_matrix[i][u] + 1;
            q.push(v);
          }
        }
      }
    }
  } else if (subtask == 2 || subtask == 3) {
    tree_sz.resize(n);
    tree_parent.resize(n, -1);
    tree_vis.resize(n, 0);
  }
}

int solve_general() {
  vector<bool> candidate(n_vert, true);
  int cand_count = n_vert;

  while (cand_count > 1) {
    int best_u = 0;
    int min_max_bucket = 1e9;

    for (int u = 0; u < n_vert; ++u) {
      int prime_bucket = candidate[u] ? 1 : 0;
      int max_bucket = prime_bucket;

      for (int v : adj[u]) {
        int count_v = 0;
        for (int w = 0; w < n_vert; ++w) {
          if (candidate[w]) {
            if (dist_matrix[u][w] == dist_matrix[v][w] + 1) {
              count_v++;
            }
          }
        }
        max_bucket = max(max_bucket, count_v);
      }

      if (max_bucket < min_max_bucket) {
        min_max_bucket = max_bucket;
        best_u = u;
      }
    }

    int res = nav(best_u);
    if (res == -1) {
      return best_u;
    }

    int x = edges_list[res].first;
    int y = edges_list[res].second;

    int new_count = 0;
    for (int w = 0; w < n_vert; ++w) {
      if (candidate[w]) {
        if (dist_matrix[best_u][w] ==
                dist_matrix[best_u][x] + 1 + dist_matrix[y][w] ||
            dist_matrix[best_u][w] ==
                dist_matrix[best_u][y] + 1 + dist_matrix[x][w]) {
          candidate[w] = true;
          new_count++;
        } else {
          candidate[w] = false;
        }
      }
    }
    cand_count = new_count;
  }

  for (int i = 0; i < n_vert; ++i) {
    if (candidate[i])
      return i;
  }
  return 0;
}

void build_tree_order(int start_node, const vector<bool> &active,
                      vector<int> &order) {
  tree_token++;
  order.clear();

  tree_vis[start_node] = tree_token;
  tree_parent[start_node] = -1;

  static vector<int> q_buf;
  q_buf.clear();
  q_buf.push_back(start_node);

  size_t head = 0;
  while (head < q_buf.size()) {
    int u = q_buf[head++];
    order.push_back(u);
    for (int v : adj[u]) {
      if (active[v] && tree_vis[v] != tree_token) {
        tree_vis[v] = tree_token;
        tree_parent[v] = u;
        q_buf.push_back(v);
      }
    }
  }
}

int find_tree_centroid(int start_node, const vector<bool> &active) {
  static vector<int> order;
  build_tree_order(start_node, active, order);

  int total = order.size();
  for (int i = order.size() - 1; i >= 0; --i) {
    int u = order[i];
    tree_sz[u] = 1;
    for (int v : adj[u]) {
      if (active[v] && v != tree_parent[u]) {
        tree_sz[u] += tree_sz[v];
      }
    }
  }

  int current = start_node;
  int p = -1;
  while (true) {
    int heavy_child = -1;
    for (int v : adj[current]) {
      if (v != p && active[v]) {
        if (tree_sz[v] > total / 2) {
          heavy_child = v;
          break;
        }
      }
    }
    if (heavy_child != -1) {
      p = current;
      current = heavy_child;
    } else {
      return current;
    }
  }
}

int solve_tree() {
  vector<bool> active(n_vert, true);
  int active_count = n_vert;

  static vector<int> q_buf2;

  while (active_count > 1) {
    int start_node = -1;
    for (int i = 0; i < n_vert; ++i) {
      if (active[i]) {
        start_node = i;
        break;
      }
    }

    int centroid = find_tree_centroid(start_node, active);

    int res = nav(centroid);
    if (res == -1) {
      return centroid;
    }

    int a = edges_list[res].first;
    int b = edges_list[res].second;
    int v_node = (a == centroid) ? b : ((b == centroid) ? a : -1);
    if (v_node == -1) {
      v_node = active[a] ? a : b;
    }

    tree_token++;
    tree_vis[centroid] = tree_token;
    tree_vis[v_node] = tree_token;

    q_buf2.clear();
    q_buf2.push_back(v_node);

    static vector<int> new_comp;
    new_comp.clear();
    new_comp.push_back(v_node);

    size_t head = 0;
    while (head < q_buf2.size()) {
      int curr = q_buf2[head++];
      for (int neighbor : adj[curr]) {
        if (active[neighbor] && tree_vis[neighbor] != tree_token) {
          tree_vis[neighbor] = tree_token;
          new_comp.push_back(neighbor);
          q_buf2.push_back(neighbor);
        }
      }
    }

    fill(active.begin(), active.end(), false);
    for (int node : new_comp) {
      active[node] = true;
    }
    active_count = new_comp.size();
  }

  for (int i = 0; i < n_vert; ++i) {
    if (active[i])
      return i;
  }
  return 0;
}

int findPrime() {
  if (subtask_id == 1 || subtask_id == 4) {
    return solve_general();
  } else {
    return solve_tree();
  }
}
