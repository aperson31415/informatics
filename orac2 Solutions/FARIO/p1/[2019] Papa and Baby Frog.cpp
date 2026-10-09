#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

struct SegmentTree {
    int n;
    vector<multiset<pair<int, int>>> tree; // stores pairs of {in_B, depth_B}

    SegmentTree(int n) : n(n), tree(4 * n + 4) {}

    void insert(int node, int l, int r, int pos, pair<int, int> val) {
        tree[node].insert(val);
        if (l == r) return;
        int mid = (l + r) / 2;
        if (pos <= mid) insert(2 * node, l, mid, pos, val);
        else insert(2 * node + 1, mid + 1, r, pos, val);
    }

    void remove(int node, int l, int r, int pos, pair<int, int> val) {
        tree[node].erase(tree[node].find(val));
        if (l == r) return;
        int mid = (l + r) / 2;
        if (pos <= mid) remove(2 * node, l, mid, pos, val);
        else remove(2 * node + 1, mid + 1, r, pos, val);
    }

    bool query(int node, int l, int r, int ql, int qr, int x_min, int x_max, int max_depth_b) {
        if (ql > r || qr < l) return false;
        if (ql <= l && r <= qr) {
            auto it = tree[node].lower_bound({x_min, -1});
            while (it != tree[node].end() && it->first <= x_max) {
                if (it->second <= max_depth_b) return true;
                ++it;
            }
            return false;
        }
        int mid = (l + r) / 2;
        return query(2 * node, l, mid, ql, qr, x_min, x_max, max_depth_b) ||
               query(2 * node + 1, mid + 1, r, ql, qr, x_min, x_max, max_depth_b);
    }
};

vector<int> compute_jumps(int n, const vector<long long>& h, bool is_papa) {
    vector<int> left_jump(n + 1, 0), right_jump(n + 1, 0);
    stack<int> st;

    // Find previous greater/smaller
    for (int i = 1; i <= n; ++i) {
        while (!st.empty() && (is_papa ? h[st.top()] <= h[i] : h[st.top()] >= h[i])) {
            st.pop();
        }
        if (!st.empty()) left_jump[i] = st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    // Find next greater/smaller
    for (int i = n; i >= 1; --i) {
        while (!st.empty() && (is_papa ? h[st.top()] <= h[i] : h[st.top()] >= h[i])) {
            st.pop();
        }
        if (!st.empty()) right_jump[i] = st.top();
        st.push(i);
    }

    vector<int> jump(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int l = left_jump[i];
        int r = right_jump[i];
        if (l == 0 && r == 0) continue;
        if (l == 0) {
            jump[i] = r;
        } else if (r == 0) {
            jump[i] = l;
        } else {
            int dist_l = i - l;
            int dist_r = r - i;
            // Rightmost preferred on tie
            if (dist_r <= dist_l) jump[i] = r;
            else jump[i] = l;
        }
    }
    return jump;
}

// Euler tour variables for Baby's tree
int timer_b = 0;
vector<int> in_b, out_b, depth_b;
vector<vector<int>> baby_children;

void dfs_baby(int u, int d) {
    in_b[u] = ++timer_b;
    depth_b[u] = d;
    for (int v : baby_children[u]) {
        dfs_baby(v, d + 1);
    }
    out_b[u] = timer_b;
}

// Papa's tree traversal variables
vector<vector<int>> papa_children;
vector<bool> is_potential_home;
SegmentTree* seg_tree_ptr = nullptr;
int k_limit = 0;

void dfs_papa(int u, int current_depth) {
    if (current_depth > 0) {
        int ql = max(0, current_depth - k_limit);
        int qr = current_depth - 1;
        if (ql <= qr) {
            if (seg_tree_ptr->query(1, 0, seg_tree_ptr->n, ql, qr, in_b[u], out_b[u], depth_b[u] + k_limit)) {
                is_potential_home[u] = true;
            }
        }
    }

    // Insert current node into Segment Tree AFTER the query
    seg_tree_ptr->insert(1, 0, seg_tree_ptr->n, current_depth, {in_b[u], depth_b[u]});

    // Recurse to children
    for (int v : papa_children[u]) {
        dfs_papa(v, current_depth + 1);
    }

    seg_tree_ptr->remove(1, 0, seg_tree_ptr->n, current_depth, {in_b[u], depth_b[u]});
}
int main() {
    int n;
    cin >> n >> k_limit;
    k_limit = min(k_limit, n);

    vector<long long> h(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
    }

    vector<int> P = compute_jumps(n, h, true);
    vector<int> B = compute_jumps(n, h, false);

    // Build Baby's tree and run Euler tour
    baby_children.assign(n + 1, vector<int>());
    vector<int> baby_roots;
    for (int i = 1; i <= n; ++i) {
        if (B[i] != 0) {
            baby_children[B[i]].push_back(i);
        } else {
            baby_roots.push_back(i);
        }
    }

    in_b.resize(n + 1);
    out_b.resize(n + 1);
    depth_b.resize(n + 1);
    for (int root : baby_roots) {
        dfs_baby(root, 0);
    }

    // Build Papa's tree
    papa_children.assign(n + 1, vector<int>());
    vector<int> papa_roots;
    for (int i = 1; i <= n; ++i) {
        if (P[i] != 0) {
            papa_children[P[i]].push_back(i);
        } else {
            papa_roots.push_back(i);
        }
    }

    // Initialize Segment Tree and run Papa DFS
    SegmentTree st(n + 1);
    seg_tree_ptr = &st;
    is_potential_home.assign(n + 1, false);

    for (int root : papa_roots) {
        dfs_papa(root, 0);
    }

    // Output result
    for (int i = 1; i <= n; ++i) {
        cout << (is_potential_home[i] ? '1' : '0');
    }
}
