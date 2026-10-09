#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Track {
    int x1, y1, x2, y2;
};

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return false;

        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

int main() {
    ifstream cin("trainin.txt");
    ofstream cout("trainout.txt");

    int N;
    cin >> N;

    vector<Track> tracks(N);
    for (int i = 0; i < N; i++) {
        cin >> tracks[i].x1 >> tracks[i].y1
            >> tracks[i].x2 >> tracks[i].y2;
    }

    vector<Edge> edges;
    ll totalRevenue = 0;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int x = 0, y = 0;
            bool intersects = false;

            bool vertI = tracks[i].x1 == tracks[i].x2;
            bool vertJ = tracks[j].x1 == tracks[j].x2;

            if (vertI != vertJ) {
                int v = vertI ? i : j;
                int h = vertI ? j : i;

                x = tracks[v].x1;
                y = tracks[h].y1;

                int vxmin = min(tracks[v].y1, tracks[v].y2);
                int vxmax = max(tracks[v].y1, tracks[v].y2);
                int hymin = min(tracks[h].x1, tracks[h].x2);
                int hymax = max(tracks[h].x1, tracks[h].x2);

                if (vxmin <= y && y <= vxmax &&
                    hymin <= x && x <= hymax) {
                    intersects = true;
                }
            }

            if (intersects) {
                int w = abs(x) + abs(y);
                totalRevenue += w;
                edges.push_back({i, j, w});
            }
        }
    }

    sort(edges.begin(), edges.end());

    DSU dsu(N);
    ll mstWeight = 0;
    int used = 0;

    for (auto e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mstWeight += e.w;
            used++;

            if (used == N - 1) break;
        }
    }

    cout << totalRevenue - mstWeight << '\n';

    return 0;
}
