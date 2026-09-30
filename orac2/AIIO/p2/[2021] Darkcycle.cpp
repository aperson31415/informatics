#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
const long long INF = 1e18;
 
struct Event {
    long long pos;
    int type; // 0 for guard tower, 1 for workshop
    long long s_or_u;
    long long f_or_c;
    int id;
};
 
struct SegmentTree {
    int n;
    vector<long long> tree;
    vector<long long> lazy;
 
    SegmentTree(int n) : n(n), tree(4 * n, INF), lazy(4 * n, 0) {}
 
    void push(int node) {
        if (lazy[node] != 0) {
            tree[2 * node] += lazy[node];
            lazy[2 * node] += lazy[node];
            tree[2 * node + 1] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
            lazy[node] = 0;
        }
    }
 
    void update_point(int node, int start, int end, int idx, long long val) {
        if (start == end) {
            tree[node] = min(tree[node], val);
            return;
        }
        push(node);
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid)
            update_point(2 * node, start, mid, idx, val);
        else
            update_point(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
 
    void range_add(int node, int start, int end, int l, int r, long long val) {
        if (r < start || end < l)
            return;
        if (l <= start && end <= r) {
            tree[node] += val;
            lazy[node] += val;
            return;
        }
        push(node);
        int mid = (start + end) / 2;
        range_add(2 * node, start, mid, l, r, val);
        range_add(2 * node + 1, mid + 1, end, l, r, val);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
 
    long long query_min(int node, int start, int end, int l, int r) {
        if (r < start || end < l)
            return INF;
        if (l <= start && end <= r)
            return tree[node];
        push(node);
        int mid = (start + end) / 2;
        return min(query_min(2 * node, start, mid, l, r),
                   query_min(2 * node + 1, mid + 1, end, l, r));
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    long long D;
    int T, W; cin >> D >> T>> W;
 
    vector<Event> events;
    vector<long long> stealth_vals;
    stealth_vals.push_back(0);
 
    for (int i = 0; i < T; ++i) {
        long long a, s, f;
        cin >> a >> s >> f;
        events.push_back({a, 0, s, f, i});
        stealth_vals.push_back(s);
    }
 
    for (int i = 0; i < W; ++i) {
        long long b, u, c;
        cin >> b >> u >> c;
        events.push_back({b, 1, u, c, i});
        stealth_vals.push_back(u);
    }
 
    // Sort events by position along the highway
    sort(events.begin(), events.end(), [](const Event& x, const Event& y) {
        return x.pos < y.pos;
    });
 
    // Coordinate compression for stealth levels
    sort(stealth_vals.begin(), stealth_vals.end());
    stealth_vals.erase(unique(stealth_vals.begin(), stealth_vals.end()), stealth_vals.end());
 
    int m = stealth_vals.size();
    SegmentTree st(m);
 
    int zero_idx = lower_bound(stealth_vals.begin(), stealth_vals.end(), 0) - stealth_vals.begin();
    st.update_point(1, 0, m - 1, zero_idx, 0);
 
    for (const auto& ev : events) {
        if (ev.type == 0) {
            // Guard tower event
            long long s = ev.s_or_u;
            long long f = ev.f_or_c;
            int idx = lower_bound(stealth_vals.begin(), stealth_vals.end(), s) - stealth_vals.begin();
            if (idx > 0) {
                st.range_add(1, 0, m - 1, 0, idx - 1, f);
            }
        } else {
            // Workshop event
            long long u = ev.s_or_u;
            long long c = ev.f_or_c;
            int idx = lower_bound(stealth_vals.begin(), stealth_vals.end(), u) - stealth_vals.begin();
            
            long long min_prev = INF;
            if (idx > 0) {
                min_prev = st.query_min(1, 0, m - 1, 0, idx - 1);
            }
            if (min_prev < INF) {
                st.update_point(1, 0, m - 1, idx, min_prev + c);
            }
        }
    }
 
    long long ans = st.query_min(1, 0, m - 1, 0, m - 1);
    cout << ans;
}
