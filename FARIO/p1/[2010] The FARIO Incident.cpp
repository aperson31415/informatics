#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

const int MOD = 1000003;

struct mi {
    int v;
    explicit operator int() const { return v; }
    mi() { v = 0; }
    mi(long long _v) : v(_v % MOD) { v += (v < 0) * MOD; }
};
mi &operator+=(mi &a, mi b) {
    if ((a.v += b.v) >= MOD) a.v -= MOD;
    return a;
}
mi &operator-=(mi &a, mi b) {
    if ((a.v -= b.v) < 0) a.v += MOD;
    return a;
}
mi operator+(mi a, mi b) { return a += b; }
mi operator-(mi a, mi b) { return a -= b; }
mi operator*(mi a, mi b) { return mi((long long)a.v * b.v); }
mi &operator*=(mi &a, mi b) { return a = a * b; }
mi pow(mi a, long long p) {
    assert(p >= 0);
    return p == 0 ? 1 : pow(a * a, p / 2) * (p & 1 ? a : 1);
}
mi inv(mi a) {
    assert(a.v != 0);
    return pow(a, MOD - 2);
}
mi operator/(mi a, mi b) { return a * inv(b); }

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, d; cin >> n >> d;
    const vector<vector<int>> adj = {{}, {2, 4}, {1, 3, 5}, {2, 6}, {1, 5, 7}, {2, 4, 6, 8}, {3, 5, 9}, {4, 8}, {5, 7, 9}, {6, 8}};

    if(n == 1) {
        cout << 1;
        return 0;
    }

    vector<mi> count(10, 0), prev_count(10, 0);
    prev_count[d] = 1;

    for(int i = 0; i < n - 1; i++) {
        for(int num = 1; num < 10; num++) {
            for(int neighbour : adj[num]) {
                count[num] += prev_count[neighbour];
            }
        }

        prev_count = count;
        count = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    }

    mi res = 0;
    for(int i = 1; i <= 9; i++) {
        res += prev_count[i];
    }

    cout << res.v;
}