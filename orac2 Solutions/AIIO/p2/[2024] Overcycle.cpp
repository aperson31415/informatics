// kinda tight on time limit - takes 0.75s

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL << 62);

struct Edge {
    int to;
    ll w;
};

vector<ll> dijkstra(int src, const vector<vector<Edge>>& g) {
    int n = (int)g.size() - 1;

    vector<ll> dist(n + 1, INF);
    priority_queue<pair<ll,int>,
                   vector<pair<ll,int>>,
                   greater<pair<ll,int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [du, u] = pq.top();
        pq.pop();

        if (du != dist[u]) continue;

        for (auto [v, w] : g[u]) {
            if (du + w < dist[v]) {
                dist[v] = du + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int N; cin >> N;

    vector<ll> pref(N + 1, 0);
    vector<vector<Edge>> g(N + 1);

    for (int i = 1; i < N; i++) {
        ll d;
        cin >> d;

        pref[i + 1] = pref[i] + d;

        g[i].push_back({i + 1, d});
        g[i + 1].push_back({i, d});
    }

    int A; cin >> A;

    for (int i = 0; i < A; i++) {
        int x; ll k;
        cin >> x >> k;

        g[1].push_back({x, k});
        g[x].push_back({1, k});
    }

    int B; cin >> B;

    for (int i = 0; i < B; i++) {
        int y; ll l;
        cin >> y >> l;

        g[N].push_back({y, l});
        g[y].push_back({N, l});
    }

    // Shortest distances from 1 and N.
    vector<ll> d1 = dijkstra(1, g);
    vector<ll> dN = dijkstra(N, g);

    ll d1N = d1[N];

    int Q; cin >> Q;

    while (Q--) {
        int s, t; cin >> s >> t;

        ll ans = pref[t] - pref[s];

        // s -> 1 -> t
        ans = min(ans, d1[s] + d1[t]);

        // s -> N -> t
        ans = min(ans, dN[s] + dN[t]);

        // s -> 1 -> N -> t
        ans = min(ans, d1[s] + d1N + dN[t]);

        // s -> N -> 1 -> t
        ans = min(ans, dN[s] + d1N + d1[t]);

        cout << ans << '\n';
    }
}

