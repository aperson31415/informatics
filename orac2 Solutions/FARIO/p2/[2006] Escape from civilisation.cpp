#include <bits/stdc++.h>
using namespace std;

const vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void bfs(const vector<pair<int, int>>& civilisations, vector<vector<int>>& dist, vector<vector<bool>>& visited, int h, int w) {
    queue<pair<int, int>> q;

    for (auto elem : civilisations) {
        visited[elem.first][elem.second] = true;
        dist[elem.first][elem.second] = 0;
        q.push(elem);
    }

    while (!q.empty()) {
        auto [r, c] = q.front(); 
        q.pop();

        for (auto [deltx, delty] : dirs) {
            int nr = r + deltx;
            int nc = c + delty;

            if (nr < 0 || nc < 0 || nr >= h || nc >= w) continue;
            if (visited[nr][nc]) continue; 

            visited[nr][nc] = true;
            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc});
        }
    }
}

unsigned io = [](){ ios_base::sync_with_stdio(0); cin.tie(0); return 0; }();

int main() {
    int w, h; 
    cin >> w >> h;
    
    vector<vector<int>> matrix(h, vector<int>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> matrix[i][j];
        }
    }

    vector<pair<int, int>> civilisations;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (matrix[i][j] == 1) {
                civilisations.push_back({i, j});
            }
        }
    }

    vector<vector<int>> dist(h, vector<int>(w, 0));
    vector<vector<bool>> visited(h, vector<bool>(w, false));

    bfs(civilisations, dist, visited, h, w);

    int res = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            res = max(res, dist[i][j]);
        }
    }

    cout << res << "\n";
}
