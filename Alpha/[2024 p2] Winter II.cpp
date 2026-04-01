// Bruh so long

#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

struct point {
    int x, y;
    bool operator<(const point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    bool operator==(const point& other) const {
        return x == other.x && y == other.y;
    }
};

bool upsort(point a, point b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
bool downsort(point a, point b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y > b.y;
}
bool rightsort(point a, point b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}
bool leftsort(point a, point b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x > b.x;
}

int N;
map<point, bool> visited;
map<point, vector<pair<point, int>>> adj; 

void dfs(point s) {
    if (visited[s]) return;
    visited[s] = true;
    for (auto& u : adj[s]) {
        dfs(u.first);
    }
}

void dijkstra(point start_node, point end_node) {
    priority_queue<pair<long long, point>, vector<pair<long long, point>>, greater<pair<long long, point>>> q;

    map<point, long long> distance;
    map<point, bool> processed;

    distance[start_node] = 0;
    q.push({0, start_node});

    while(!q.empty()) {
        point a = q.top().second; 
        q.pop();

        if(processed[a]) continue;
        processed[a] = true;

        if(a == end_node) {
            cout << distance[a] << endl;
            return;
        }

        for(auto& edge : adj[a]) {
            point b = edge.first;
            int w = edge.second;
            
            // If distance[b] hasn't been set, treat as infinity
            if (distance.find(b) == distance.end() || distance[a] + w < distance[b]) {
                distance[b] = distance[a] + w;
                q.push({distance[b], b});
            }
        }
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> N;
    
    vector<point> coords(N);
    point start_pt, end_pt;

    for(int i = 0; i < N; i++) {
        cin >> coords[i].x >> coords[i].y;
        if(i == 0) start_pt = coords[i];
        if(i == N - 1) end_pt = coords[i];
    }

    // Helper to build edges based on your sorting logic
    auto build_edges = [&](vector<point> vec, auto cmp) {
        sort(vec.begin(), vec.end(), cmp);
        for(int i = 0; i < N - 1; i++) {
            point cur = vec[i];
            point nxt = vec[i+1];
            // Only connect if they share the required axis (x for up/down, y for left/right)
            if(cur.x == nxt.x || cur.y == nxt.y) {
                int dist = abs(cur.x - nxt.x) + abs(cur.y - nxt.y);
                adj[cur].push_back({nxt, dist});
            }
        }
    };

    build_edges(coords, upsort);
    build_edges(coords, downsort);
    build_edges(coords, rightsort);
    build_edges(coords, leftsort);

    dfs(start_pt);
    if(!visited[end_pt]) {
        cout << -1 << endl;
    } else {
        dijkstra(start_pt, end_pt);
    }
}