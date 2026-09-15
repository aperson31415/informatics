#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

struct Edge {
    int u, v, c;
    bool operator<(const Edge& other) const {
        return c < other.c;
    }
};

int main() {
    int n, m; cin >> n >> m;

    vector<int> country(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> country[i];
    }

    vector<Edge> edges(m);
    long long total_initial_cost = 0;
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].c;
        total_initial_cost += edges[i].c;
    }

    sort(edges.begin(), edges.end());

    DSU city_dsu(n);
    long long internal_mst_cost = 0;

    for (int i = 0; i < m; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        int c = edges[i].c;

        if (country[u] == country[v]) {
            if (city_dsu.unite(u, v)) {
                internal_mst_cost += c;
            }
        }
    }

    DSU country_dsu(n);
    long long inter_mst_cost = 0;
    
    for (int i = 0; i < m; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        int c = edges[i].c;

        if (country[u] != country[v]) {
            int cu = country[u];
            int cv = country[v];
            if (country_dsu.unite(cu, cv)) {
                inter_mst_cost += c;
            }
        }
    }

    long long total_kept_cost = internal_mst_cost + inter_mst_cost;
    long long max_savings = total_initial_cost - total_kept_cost;

    cout << max_savings;
}
