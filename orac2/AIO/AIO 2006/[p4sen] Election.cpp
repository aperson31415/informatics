#include <bits/stdc++.h>
using namespace std;

struct Window {
    int x, y, wi, hi;
};

int main() {
    int w, h, n; cin >> w >> h >> n;

    vector<Window> windows(n);
    vector<int> x_coords;
    x_coords.push_back(0);
    x_coords.push_back(w);

    for (int i = 0; i < n; ++i) {
        cin >> windows[i].x >> windows[i].y >> windows[i].wi >> windows[i].hi;
        x_coords.push_back(windows[i].x);
        x_coords.push_back(windows[i].x + windows[i].wi);
    }

    sort(x_coords.begin(), x_coords.end());
    x_coords.erase(unique(x_coords.begin(), x_coords.end()), x_coords.end());

    long long max_area = 0;
    int num_x = x_coords.size();

    // Iterate over all pairs of X-coordinates to form vertical strips
    for (int i = 0; i < num_x; ++i) {
        for (int j = i + 1; j < num_x; ++j) {
            long long xl = x_coords[i];
            long long xr = x_coords[j];
            long long width = xr - xl;

            if (width * h <= max_area) {
                continue;
            }

            // Collect all windows that overlap horizontally with this strip [xl, xr]
            vector<pair<int, int>> blocking_intervals;
            for (int k = 0; k < n; ++k) {
                if (windows[k].x < xr && windows[k].x + windows[k].wi > xl) {
                    blocking_intervals.push_back({windows[k].y, windows[k].y + windows[k].hi});
                }
            }

            // If no windows block this strip, the maximum height is the whole wall h
            if (blocking_intervals.empty()) {
                max_area = max(max_area, width * h);
                continue;
            }

            sort(blocking_intervals.begin(), blocking_intervals.end());

            vector<pair<int, int>> merged;
            for (const auto& interval : blocking_intervals) {
                if (merged.empty() || merged.back().second < interval.first) {
                    merged.push_back(interval);
                } else {
                    merged.back().second = max(merged.back().second, interval.second);
                }
            }

            long long max_height = 0;
            int current_y = 0;

            for (const auto& interval : merged) {
                max_height = max(max_height, (long long)(interval.first - current_y));
                current_y = max(current_y, interval.second);
            }

            max_height = max(max_height, (long long)(h - current_y));

            long long area = width * max_height;
            if (area > max_area) {
                max_area = area;
            }
        }
    }

    cout << max_area;
}
