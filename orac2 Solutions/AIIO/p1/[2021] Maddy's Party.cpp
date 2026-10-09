#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Range {
    ll x, a, b;
};

struct DSU {
    vector<int> p, sz;
    int components;

    DSU(int n) : p(n), sz(n, 1), components(n) {
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) return;

        if (sz[a] < sz[b]) swap(a, b);

        p[b] = a;
        sz[a] += sz[b];
        --components;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    int R;
    cin >> N >> R;

    vector<Range> v(R);

    for (auto &e : v) {
        cin >> e.x >> e.a >> e.b;
    }

    DSU dsu(R);

    vector<int> ord(R);
    iota(ord.begin(), ord.end(), 0);

    sort(ord.begin(), ord.end(), [&](int i, int j) {
        if (v[i].a != v[j].a)
            return v[i].a < v[j].a;
        return v[i].b < v[j].b;
    });

    ll maxB = -1;
    int best = -1;

    for (int i : ord) {
        if (best != -1 && v[i].a <= maxB) {
            dsu.unite(i, best);

            if (v[i].b > maxB) {
                maxB = v[i].b;
                best = i;
            }
        } else {
            maxB = v[i].b;
            best = i;
        }
    }

    sort(ord.begin(), ord.end(), [&](int i, int j) {
        return v[i].x < v[j].x;
    });

    for (int i = 1; i < R; ++i) {
        int u = ord[i - 1];
        int w = ord[i];

        if (v[u].x == v[w].x)
            dsu.unite(u, w);
    }

    sort(ord.begin(), ord.end(), [&](int i, int j) {
        return v[i].a < v[j].a;
    });

    vector<int> byX(R);
    iota(byX.begin(), byX.end(), 0);

    sort(byX.begin(), byX.end(), [&](int i, int j) {
        return v[i].x < v[j].x;
    });

    priority_queue<pair<ll, int>> pq;
    int ptr = 0;

    for (int i : byX) {
        while (ptr < R && v[ord[ptr]].a <= v[i].x) {
            int j = ord[ptr++];
            pq.push({v[j].b, j});
        }

        if (!pq.empty() && pq.top().first >= v[i].x) {
            dsu.unite(i, pq.top().second);
        }
    }

    vector<pair<ll, ll>> intervals;
    intervals.reserve(R);

    for (const auto &e : v)
        intervals.push_back({e.a, e.b});

    sort(intervals.begin(), intervals.end());

    vector<pair<ll, ll>> merged;

    for (auto [l, r] : intervals) {
        if (merged.empty() || l > merged.back().second + 1) {
            merged.push_back({l, r});
        } else {
            merged.back().second =
                max(merged.back().second, r);
        }
    }

    ll covered = 0;

    for (auto [l, r] : merged)
        covered += r - l + 1;

    vector<ll> centers;

    for (const auto &e : v)
        centers.push_back(e.x);

    sort(centers.begin(), centers.end());
    centers.erase(unique(centers.begin(), centers.end()),
                  centers.end());

    for (ll x : centers) {
        auto it = upper_bound(
            merged.begin(), merged.end(),
            make_pair(x, LLONG_MAX)
        );

        bool inside = false;

        if (it != merged.begin()) {
            --it;
            inside = (it->first <= x && x <= it->second);
        }

        if (!inside)
            ++covered;
    }

    ll answer = dsu.components + (N - covered);

    cout << answer << '\n';

    return 0;
}
