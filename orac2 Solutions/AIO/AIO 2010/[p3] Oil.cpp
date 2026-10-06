#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

struct point {
    int x, y;
};

vector<vector<bool>> visited;
vector<vector<int>> dist;
vector<vector<int>> matrix;
vector<vector<vector<point>>> adj;
int R, C, K;

void bfs(int x, int y) {
    queue<point> q;
    visited[y][x] = true;
    dist[y][x] = 0;
    q.push({x, y});
    while (!q.empty()) {
        point s = q.front(); q.pop();
        if(dist[s.y][s.x] >= K) continue;
        // process node s
        for (point u : adj[s.y][s.x]) {
            if (visited[u.y][u.x]) continue;
            visited[u.y][u.x] = true;
            dist[u.y][u.x] = dist[s.y][s.x] + 1;
            q.push(u);
        }
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    cin >> R >> C >> K;
    matrix.resize(R + 2, vector<int>(C + 2));
    adj.resize(R + 2, vector<vector<point>>(C + 2));
    visited.resize(R + 2, vector<bool>(C + 2));
    dist.resize(R + 2, vector<int>(C + 2));
    point start;

    char x;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> x;
            if(x == '#') matrix[i + 1][j + 1] = 1;
            else if(x == '.') matrix[i + 1][j + 1] = 0;
            else if(x == '$') {start = {j + 1, i + 1}; matrix[i + 1][j + 1] = -1;}
        }
    }

    vector<point> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            for(auto& [deltx, delty] : dirs) {
                if(matrix[i + delty][j + deltx] == 0 and (matrix[i][j] == 0 or matrix[i][j] == -1)) {
                    adj[i][j].push_back({j + deltx, i + delty});
                    adj[i + delty][j + deltx].push_back({j, i});
                }
            }
        }
    }

    bfs(start.x, start.y);

    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            if(matrix[i][j] == 1) cout << '#';
            else if(matrix[i][j] == -1) cout << '$';
            else {
                if(visited[i][j]) cout << '*';
                else cout << '.';
            }
        }
        cout << '\n';
    }
}