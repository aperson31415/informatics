#include <bits/stdc++.h>
using namespace std;

int main() {
    int H, W; cin >> H >> W;

    vector<string> grid(H);
    for (int i = 0; i < H; ++i) {
        cin >> grid[i];
    }

    vector<vector<bool>> visited(H, vector<bool>(W, false));
    int max_overall_diameter = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int r = 0; r < H; ++r) {
        for (int c = 0; c < W; ++c) {
            if (grid[r][c] == 'X' && !visited[r][c]) {
                int min_sum = INT_MAX, max_sum = INT_MIN;
                int min_diff = INT_MAX, max_diff = INT_MIN;

                queue<pair<int, int>> q;
                q.push({r, c});
                visited[r][c] = true;

                while (!q.empty()) {
                    auto [curr_r, curr_c] = q.front();
                    q.pop();

                    int s = curr_r + curr_c;
                    int d = curr_r - curr_c;

                    if (s < min_sum) min_sum = s;
                    if (s > max_sum) max_sum = s;
                    if (d < min_diff) min_diff = d;
                    if (d > max_diff) max_diff = d;

                    for (int i = 0; i < 4; ++i) {
                        int nr = curr_r + dr[i];
                        int nc = curr_c + dc[i];

                        if (nr >= 0 && nr < H && nc >= 0 && nc < W && 
                            grid[nr][nc] == 'X' && !visited[nr][nc]) {
                            visited[nr][nc] = true;
                            q.push({nr, nc});
                        }
                    }
                }

                int component_diameter = max(max_sum - min_sum, max_diff - min_diff);
                max_overall_diameter = max(max_overall_diameter, component_diameter);
            }
        }
    }

    cout << max_overall_diameter;
}
