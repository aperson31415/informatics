#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 2e18;
struct edge {
    int to;
    int weight;
};

struct node {
    int dist;
    int u;
    int src;

    bool operator>(const node& other) const {
        return dist > other.dist;
    }
};

signed main() {
    int V, E, K; cin >> V >> E >> K;

    vector<int> grounded(K);
    vector<bool> is_grounded(V + 1, false);
    for (int i = 0; i < K; ++i) {
        cin >> grounded[i];
        is_grounded[grounded[i]] = true;
    }

    vector<vector<edge>> adj(V + 1);
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> dist(V + 1, INF);
    vector<int> source(V + 1, -1);

    priority_queue<node, vector<node>, greater<node>> pq;

    // main multi-source dijkstra
    for (int i = 0; i < K; ++i) {
        int g_node = grounded[i];
        dist[g_node] = 0;
        source[g_node] = i;
        pq.push({0, g_node, i});
    }

    int shortest_path = INF;

    while (!pq.empty()) {
        auto [d, u, src] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& adj_edge : adj[u]) {
            int v = adj_edge.to;
            int weight = adj_edge.weight;

            if (source[v] != -1 && source[v] != src) {
                shortest_path = min(shortest_path, dist[u] + dist[v] + weight);
            }

            if (d + weight < dist[v]) {
                dist[v] = d + weight;
                source[v] = src;
                pq.push({dist[v], v, src});
            }
        }
    }

    cout << shortest_path;
}
