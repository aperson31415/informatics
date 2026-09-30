#include <bits/stdc++.h>
using namespace std;
#define int long long

int dist(int x1, int y1, int x2, int y2) {
    int x = abs(x1 - x2);
    int y = abs(y1 - y2);
    return x * x + y * y;
}

signed main() {
    int r, c; 
    pair<int, int> p, f;
    cin >> r >> c >> p.first >> p.second >> f.first >> f.second;
    int q; cin >> q;
    bool is_diagonal = (abs(f.second - p.second) == abs(f.first - p.first));

    for (int i = 0; i < q; i++) {
        pair<int, int> query;
        cin >> query.first >> query.second;

        if (is_diagonal) {
            int dist_p = dist(query.first, query.second, p.first, p.second);
            int dist_f = dist(query.first, query.second, f.first, f.second);

            if (dist_p < dist_f) cout << "WATER\n";
            else if (dist_p > dist_f) cout << "LAVA\n";
            else cout << "MOUNTAINS\n";
        } else {
            int dist_p = abs(query.first - p.first) + abs(query.second - p.second);
            int dist_f = abs(query.first - f.first) + abs(query.second - f.second);

            if (dist_p < dist_f) cout << "WATER\n";
            else if (dist_f < dist_p) cout << "LAVA\n";
            else cout << "MOUNTAINS\n";
        }
    }
}
