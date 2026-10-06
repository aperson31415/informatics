#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct SegTree {
    int n;
    vector<ll> tree;

    SegTree(const vector<ll>& a) {
        n = (int)a.size() - 1;
        tree.resize(4 * n);
        build(1, 1, n, a);
    }

    void build(int node, int l, int r, const vector<ll>& a) {
        if (l == r) {
            tree[node] = a[l];
            return;
        }

        int mid = (l + r) / 2;
        build(node * 2, l, mid, a);
        build(node * 2 + 1, mid + 1, r, a);
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    ll query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return LLONG_MAX / 4;
        if (ql <= l && r <= qr) return tree[node];

        int mid = (l + r) / 2;
        return min(query(node * 2, l, mid, ql, qr),
                   query(node * 2 + 1, mid + 1, r, ql, qr));
    }

    ll query(int l, int r) {
        if (l > r) return LLONG_MAX / 4;
        return query(1, 1, n, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, C;
    cin >> N >> C;

    int L = N + 1, R = 0;

    for (int i = 0; i < C; i++) {
        int x;
        cin >> x;
        L = min(L, x);
        R = max(R, x);
    }

    vector<ll> t(N), A(N), B(N);

    for (int i = 1; i < N; i++) cin >> t[i];

    for (int i = 1; i < N; i++) {
        A[i] = t[i] - i;
        B[i] = t[i] - (N - 1 - i);
    }

    SegTree segA(A), segB(B);

    auto canRight = [&](int s, int l, int r, int extra) {
        if (l > r) return true;
        return segA.query(l, r) + s - 1 - extra >= 0;
    };

    auto canLeft = [&](int s, int l, int r, int extra) {
        if (l > r) return true;
        return segB.query(l, r) + N - 1 - s - extra >= 0;
    };

    int ans = 0;

    for (int s = 1; s <= N; s++) {
        bool possible = false;

        // s -> L -> R
        if (s < L) {
            if (canRight(s, s, R - 1, 0)) possible = true;
        } else {
            if (canLeft(s, L, s - 1, 0) &&
                canRight(L, L, R - 1, s - L))
                possible = true;
        }

        // s -> R -> L
        if (!possible) {
            if (s > R) {
                if (canLeft(s, L, s - 1, 0)) possible = true;
            } else {
                if (canRight(s, s, R - 1, 0) &&
                    canLeft(R, L, R - 1, R - s))
                    possible = true;
            }
        }

        if (possible) ans++;
    }

    cout << ans << '\n';
}

