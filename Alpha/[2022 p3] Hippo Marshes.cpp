#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;
#define fio(in, out) freopen(in, "r", stdin); freopen(out, "w", stdout)

vector<bool> visited;
vector<bool> visited_rev;
vector<vector<int>> adj;
vector<vector<int>> rev_adj;

void dfs(int start) {
    if(visited[start]) return;
    visited[start] = true;
    for(auto& neighbour : adj[start]) {
        dfs(neighbour);
    }
}

void dfs_rev(int start) {
    //cout << "node " << start << endl;
    if(visited_rev[start]) return;
    visited_rev[start] = true;
    for(auto& neighbour : rev_adj[start]) {
        //cout << "node " << start << "has rev: " << neighbour << endl;
        dfs_rev(neighbour);
    }
}

int main() {
    //fio("nightin.txt", "nightout.txt");
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    adj.resize(n);
    rev_adj.resize(n);
    visited.resize(n, false);
    visited_rev.resize(n, false);

    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        rev_adj[b].push_back(a);
    }

    dfs(0);
    dfs_rev(n - 1);

    int res = 0;
    for(int i = 0; i < n; i++) {
        if(visited[i] and visited_rev[i]) {
            res++;
        }
    }

    cout << res;
}