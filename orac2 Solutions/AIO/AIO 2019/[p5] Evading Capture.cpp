%:include <bits/stdc++.h>
%:include <immintrin.h>
%:pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;
%:define print(...) printf(__VA_ARGS__)
%:define val(x) cerr<<#x<<'='<<x<<endl;

vector<vector<int>> adj;
vector<vector<bool>> visited;
vector<vector<int>> dist;

struct node {
    int num, parity;
};

void bfs(int s, int parity) {
    queue<node> q;
    visited[s][parity] = true;
    dist[s][parity] = 0;
    q.push({s, parity});
    while(!q.empty()) {
        node top = q.front(); q.pop();
        for(int u : adj[top.num]) {
            if (visited[u][1-top.parity]) continue;
            visited[u][1-top.parity] = true;
            dist[u][1-top.parity] = dist[top.num][top.parity]+1;
            q.push({u, 1-top.parity});
        }
    }
}

int io = [](){cin.tie(0)->sync_with_stdio(0);return 0;}();
int main() {
    int n, e, x, k, a, b; cin >> n >> e >> x >> k;
    adj.resize(n + 2);
    visited.resize(n + 2, {false, false});
    dist.resize(n + 2, {-1, -1});
    for(int i = 0; i < e; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    bfs(x, 0);
    /*for(int i = 0; i < n + 2; i++) {
        cout << dist[i][0] << ' ' << dist[i][1] << '\n';
    }*/ 

    int res = 0;
    for(int i = 0; i < n + 2; i++) {
        if(visited[i][k % 2] and dist[i][k % 2] <= k) {
            res++;
        }
    }

    cout << res;
}