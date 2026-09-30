#include <bits/stdc++.h>
using namespace std;

class MaxLazySegTree {
    int n;
    vector<int> tree;
    vector<bool> has_set;
    vector<int> lazy_add;

    void apply_set0(int node) {
        tree[node] = 0;
        has_set[node] = true;
        lazy_add[node] = 0;
    }

    void apply_add(int node, int val) {
        tree[node] += val;
        lazy_add[node] += val;
    }

    void push(int node) {
        if (has_set[node]) {
            apply_set0(2 * node);
            apply_set0(2 * node + 1);
            has_set[node] = false;
        }
        if (lazy_add[node] != 0) {
            apply_add(2 * node, lazy_add[node]);
            apply_add(2 * node + 1, lazy_add[node]);
            lazy_add[node] = 0;
        }
    }

    void update_add(int node, int l, int r, int ql, int qr, int val) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            apply_add(node, val);
            return;
        }
        push(node);
        int mid = l + (r - l) / 2;
        update_add(2 * node, l, mid, ql, qr, val);
        update_add(2 * node + 1, mid + 1, r, ql, qr, val);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    void update_set0(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            apply_set0(node);
            return;
        }
        push(node);
        int mid = l + (r - l) / 2;
        update_set0(2 * node, l, mid, ql, qr);
        update_set0(2 * node + 1, mid + 1, r, ql, qr);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    long long query_max(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return -1e9;
        if (ql <= l && r <= qr) return tree[node];
        push(node);
        int mid = l + (r - l) / 2;
        return max(query_max(2 * node, l, mid, ql, qr),
                        query_max(2 * node + 1, mid + 1, r, ql, qr));
    }

public:
    MaxLazySegTree(int size) {
        n = size;
        tree.assign(4 * n, 0);
        has_set.assign(4 * n, false);
        lazy_add.assign(4 * n, 0);
    }

    void range_add(int l, int r, int val = 1) {
        update_add(1, 0, n - 1, l, r, val);
    }

    void range_set_zero(int l, int r) {
        update_set0(1, 0, n - 1, l, r);
    }

    int query_max(int l, int r) {
        return query_max(1, 0, n - 1, l, r);
    }
};

signed main() {
  int n, l; cin >> n >> l;
  MaxLazySegTree tree(l);
  tree.range_set_zero(0, l-1);
  int res = 0;
  for(int i = 0; i < n; i++) {
    int a, b; cin >> a >> b;
    // set sides to 0
    tree.range_set_zero(0, a-1);
    tree.range_set_zero(b, l-1);
    // increase by 1
    tree.range_add(a, b-1, 1);
    // maximum
    res = max(res, tree.query_max(0, l-1));
  }

  cout << res;
}
