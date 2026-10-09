#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int n;
    vector<int> lazy;

    SegmentTree(int n) : n(n), lazy(4 * n + 5, 0) {}

    void push(int node) {
        if (lazy[node] == 0) return;

        lazy[node * 2] = lazy[node];
        lazy[node * 2 + 1] = lazy[node];
        lazy[node] = 0;
    }

    void update(int node, int l, int r,
                int ql, int qr, int value) {
        if (ql > r || qr < l || ql > qr) return;

        if (ql <= l && r <= qr) {
            lazy[node] = value;
            return;
        }

        push(node);

        int mid = (l + r) / 2;
        update(node * 2, l, mid, ql, qr, value);
        update(node * 2 + 1, mid + 1, r, ql, qr, value);
    }

    int query(int node, int l, int r, int pos) {
        if (lazy[node] != 0) return lazy[node];
        if (l == r) return 0;

        int mid = (l + r) / 2;

        if (pos <= mid)
            return query(node * 2, l, mid, pos);

        return query(node * 2 + 1, mid + 1, r, pos);
    }

    void update(int l, int r, int value) {
        if (l <= r)
            update(1, 1, n, l, r, value);
    }

    int query(int pos) {
        return query(1, 1, n, pos);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int W, H;
    cin >> W >> H;

    vector<int> top(W + 1), bottom(W + 1);

    for (int i = 1; i <= W; i++)
        cin >> top[i];

    for (int i = 1; i <= W; i++)
        cin >> bottom[i];

    SegmentTree seg(H);
    vector<int> lastOccurrence(H + 1, 0);

    long long horizontalCuts = 0;

    for (int i = 1; i <= W; i++) {
        seg.update(bottom[i] + 1, top[i] - 1, i);

        int heights[2] = {top[i], bottom[i]};

        for (int y : heights) {
            if (y == 0 || y == H)
                continue;

            int lastBlocker = seg.query(y);

            if (lastOccurrence[y] == 0 ||
                lastBlocker > lastOccurrence[y]) {
                horizontalCuts++;
            }

            lastOccurrence[y] = i;
        }
    }

    long long verticalCuts = 2LL * (W - 1);

    for (int i = 2; i <= W; i++) {
        if (top[i] == top[i - 1])
            verticalCuts--;

        if (bottom[i] == bottom[i - 1])
            verticalCuts--;
    }

    cout << horizontalCuts + verticalCuts << '\n';

    return 0;
}
