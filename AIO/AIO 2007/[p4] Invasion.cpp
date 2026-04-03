#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int R, C; cin >> R >> C;
    vector<vector<char>> matrix(R + 2, vector<char>(C + 2, '*'));
    
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> matrix[i + 1][j + 1];
        }
    }

    map<char, set<char>> adj;
    vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for(int i = 1; i < R + 1; i++) {
        for(int j = 1; j < C + 1; j++) {
            for(auto& [deltx, delty] : dirs) {
                if(matrix[i + delty][j + deltx] == matrix[i][j] or matrix[i + delty][j + deltx] == '*') continue;
                adj[matrix[i][j]].insert(matrix[i + delty][j + deltx]);
            }
        }
    }

    int max_size = 0;

    for(auto& [nation, neighbours] : adj) {
        if((int) neighbours.size() > max_size) {
            max_size = neighbours.size();
        }
    }

    cout << max_size;
}