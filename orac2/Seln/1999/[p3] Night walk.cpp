#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;
#define fio(in, out) freopen(in, "r", stdin); freopen(out, "w", stdout)
 
struct point {
    double x, y;
    double dist_to(const point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }
};
 
struct edge {
    int end;
    double length;
};
 
int n;
vector<vector<edge>> adj;
vector<double> dist;
 
void dijkstra(int start_node) {
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q;
    dist.assign(n + 3, 1e18); 
    vector<bool> processed(n + 3, false);
    
    dist[start_node] = 0;
    q.push({0, start_node});
    
    while (!q.empty()) {
        int a = q.top().second;
        q.pop();
        
        if (processed[a]) continue;
        processed[a] = true;
        
        for (auto& u : adj[a]) {
            double w = u.length;
            int b = u.end;
            if (dist[a] + w < dist[b]) {
                dist[b] = dist[a] + w;
                q.push({dist[b], b});
            }
        }
    }
}
 
int main() {
    fio("nightin.txt", "nightout.txt");
    cin.tie(0)->sync_with_stdio(0);
 
    point start, end;
    if (!(cin >> start.x >> start.y >> end.x >> end.y)) return 0;
    
    cin >> n;
    vector<point> points(n + 2);
    for (int i = 0; i < n; i++) cin >> points[i].x >> points[i].y;
    
    points[n] = start; 
    points[n + 1] = end;
 
    adj.resize(n + 2);
 
    for (int i = 0; i < n + 2; i++) {
        for (int j = i + 1; j < n + 2; j++) {
            double d = points[i].dist_to(points[j]);
            if (d <= 50.0) {
                adj[i].push_back({j, d});
                adj[j].push_back({i, d});
            }
        }
    }
 
    dijkstra(n);
 
    if (dist[n + 1] > 1e17) {
        cout << -1;
    } else {
        cout << fixed << setprecision(3) << dist[n + 1];
    }
}