#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;
 
vector<vector<int>> adj;
vector<bool> used;
int res = 0;
 
void dfs(int u) {
    bool valid = true;
    
    for (int v : adj[u]) {
        dfs(v);
        if (used[v]) {
            valid = false;
        }
    }
 
    if (valid) {
        used[u] = true;
        res++;
    }
}
 
signed main() {
    cin.tie(0)->sync_with_stdio(0);
 
    #ifndef local
        freopen("snurgle.in","r",stdin); freopen("snurgle.out", "w",stdout);
    #endif
 
    int n; cin >> n;
    adj.resize(n + 2);
    used.resize(n + 2);
 
    for (int i = 1; i < n; ++i) {
        int x;
        cin >> x;
        adj[x].push_back(i); 
    }
 
    dfs(n);
 
    cout << res;
}