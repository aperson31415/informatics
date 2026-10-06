#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

struct point {
    int x, y;
};

int _lg(int& x) {return 31 - __builtin_clz(x);}
int op(int x, int y) {return min(x, y);}

template <typename T>
struct SparseTable {
    int n;
    vector<vector<T>> st;
    SparseTable() {}
    SparseTable(vector<T>& arr) {
        n = arr.size();
        if (n == 0) return;

        int levels = _lg(n) + 1;
        st.assign(levels, vector<T>(n));

        for (int i = 0; i < n; i++) {
            st[0][i] = arr[i];
        }

        for (int j = 1; j < levels; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = op(st[j - 1][i],
                st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    T query(int L, int R) {
        int len = R - L + 1;
        int j = _lg(len);
        return op(st[j][L], st[j][R - (1 << j) + 1]);
    }
};

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N; cin >> N;
    vector<point> stars(N);
    for(int i = 0; i < N; i++) cin >> stars[i].x >> stars[i].y;

    // Make the min sparse table
    vector<int> lines(1000001, INT_MAX);
    for(int i = 0; i < N; i++) {
        lines[stars[i].x] = min(lines[stars[i].x], stars[i].y);
    }

    SparseTable minsptable(lines);

    int res = 0;

    // Go through pairs of stars
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(stars[i].y != stars[j].y) continue;
            if(i == j) continue;
            if(abs(stars[i].x - stars[j].x) <= 1) continue;

            int best_peaky = minsptable.query(min(stars[i].x, stars[j].x) + 1, max(stars[i].x, stars[j].x) - 1);
            if(best_peaky == INT_MAX) continue;
            if(best_peaky >= stars[i].y) continue;
            if(abs(stars[i].x - stars[j].x) > abs(best_peaky - stars[i].y)) continue;

            res = max(res, abs(stars[i].x - stars[j].x) + abs(best_peaky - stars[i].y));
        }
    }

    cout << res;
}