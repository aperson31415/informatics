#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

#define int long long

// Probably not intended solution but oh well here comes a tle or mle
template<typename T>
struct MinSegTree {
    int n;
    vector<T> tree;
    T ID = LLONG_MAX;

    MinSegTree(int n) : n(n), tree(4 * n, ID) {}

    void update(int pos, T new_val) {
        update(1, 0, n - 1, pos, new_val);
    }

    T query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

private:
    void update(int v, int tl, int tr, int pos, T new_val) {
        if (tl == tr) tree[v] = new_val;
        else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) update(2 * v, tl, tm, pos, new_val);
            else update(2 * v + 1, tm + 1, tr, pos, new_val);
            tree[v] = min(tree[2 * v], tree[2 * v + 1]);
        }
    }

    T query(int v, int tl, int tr, int l, int r) {
        if (l > r) return ID;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        return min(query(2 * v, tl, tm, l, min(r, tm)), 
               query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
    }
};

// too lazy
template<typename T>
struct MaxSegTree {
    int n;
    vector<T> tree;
    T ID = -1;

    MaxSegTree(int n) : n(n), tree(4 * n, ID) {}

    void update(int pos, T new_val) {
        update(1, 0, n - 1, pos, new_val);
    }

    T query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

private:
    void update(int v, int tl, int tr, int pos, T new_val) {
        if (tl == tr) tree[v] = new_val;
        else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) update(2 * v, tl, tm, pos, new_val);
            else update(2 * v + 1, tm + 1, tr, pos, new_val);
            tree[v] = max(tree[2 * v], tree[2 * v + 1]);
        }
    }

    T query(int v, int tl, int tr, int l, int r) {
        if (l > r) return ID;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        return max(query(2 * v, tl, tm, l, min(r, tm)), 
               query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
    }
};

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    int N; cin >> N;
    vector<int> p(N);
    for(int i = 0; i < N; i++) cin >> p[i];

    // Build segtree
    MaxSegTree<int> maxseg(N);
    MinSegTree<int> minseg(N);
    for(int i = 0; i < N; i++) {
        maxseg.update(i, p[i]);
        minseg.update(i, p[i]);
    }

    // Proccess queries
    int Q; cin >> Q;
    int t, s, x;
    for(int i = 0; i < Q; i++) {
        cin >> t;
        if(t == 1) {
            cin >> s;
        } else {
            cin >> s >> x;
            p[s - 1] = x;
            maxseg.update(s - 1, x);
            minseg.update(s - 1, x);
            continue;
        }

        if(s - 2 < 0) {
            // is leftmost
            cout << N;
        } else if(s > N - 1) {
            // is rightmost
            cout << 1;
        } else {
            int minleft = minseg.query(0, s - 2), minright = minseg.query(s, N - 1),
                maxleft = maxseg.query(0, s - 2), maxright = maxseg.query(s, N - 1);
            
            int maxleftdist = max(abs(minleft - p[s - 1]), abs(maxleft - p[s - 1]));
            int maxrightdist = max(abs(minright - p[s - 1]), abs(maxright - p[s - 1]));

            if(maxleftdist == maxrightdist) {
                cout << -1;
            } else if(maxleftdist > maxrightdist) {
                cout << 1;
            } else if(maxrightdist > maxleftdist) {
                cout << N;
            }
        }

        cout << '\n';
    }
}