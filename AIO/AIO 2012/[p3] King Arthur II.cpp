#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

vector<bool> visited;
vector<vector<int>> adj;
set<int> unvisited;

int zeroes, ones;

struct D {
    int s, ones, zeroes, curr;
};

void dfs(D stuff) {
    if (visited[stuff.s]) return;
    visited[stuff.s] = true;
    unvisited.erase(stuff.s);

    if(stuff.curr == 0) {
        stuff.zeroes++;
        zeroes++;
    } else {
        stuff.ones++;
        ones++;
    }

    // process node s
    for (int u: adj[stuff.s]) {
        if(stuff.curr == 0) {
            dfs({u, stuff.ones, stuff.zeroes, 1});
        } else {
            dfs({u, stuff.ones, stuff.zeroes, 0});
        }
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int V, E, a, b; cin >> V >> E;
    adj.resize(V);
    visited.resize(V);

    for(int i = 0; i < V; i++) {
        unvisited.insert(i);
    }

    for(int i = 0; i < E; i++) {
        cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }

    int res = 0;

    while(!unvisited.empty()) {
        zeroes = 0; ones = 0;
        dfs({*unvisited.begin(), 0, 0, 0});
        //cout << "parent " << *unvisited.begin() << ": " << max(zeroes, ones) << "\n";
        res += max(zeroes, ones);
    }

    cout << res;
}