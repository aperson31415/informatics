// Code could probably be optimised a bit more

#include <bits/stdc++.h>
using namespace std;
 
int res = 0;
vector<vector<vector<pair<int, int>>>> adj;
vector<vector<bool>> visited;
pair<int, int> pope;
 
void dfs(int sx, int sy) {
    if (visited[sx][sy] == true) return;
    if (make_pair(sx, sy) == pope) return;
    visited[sx][sy] = true;
    res++;
    //cout << sx << "," << sy << " marked." << endl;
    for (auto u: adj[sx][sy]) {
        dfs(u.first, u.second);
    }
}
 
int main() {
    int r, c; cin >> r >> c;
    visited.resize(r + 2, vector<bool>(c + 2, false));
    adj.resize(r + 2, vector<vector<pair<int, int>>>(c + 2));
    char x;
    vector<pair<int, int>> starting_points;
 
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            cin >> x;
            if(x == '*') {
                starting_points.push_back({i + 1, j + 1});
            }
 
            if(x == 'v') adj[i+1 + 1][j + 1].push_back({i + 1, j + 1});
            if(x == '>') adj[i + 1][j+1 + 1].push_back({i + 1, j + 1});
            if(x == '+') pope = {i + 1, j + 1};
        }
    }
 
    for(auto starting_point : starting_points) {
        dfs(starting_point.first, starting_point.second);
    }
 
    cout << res;
}
