#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;
 
const int MAXV = 1005;
 
int graph[MAXV][MAXV]; 
int graph_size[MAXV];
 
int deps[MAXV];
int S[MAXV], s_ptr = 0;
int dist[MAXV];
 
int kahn(int V) {
    s_ptr = 0;
    int max_dist = 1;
    int visited_count = 0;
 
    for (int i = 1; i <= V; i++) {
        dist[i] = 1;
        if (deps[i] == 0) {
            S[s_ptr++] = i;
        }
    }
 
    while (s_ptr > 0) {
        int u = S[--s_ptr];
        visited_count++;
 
        for (int i = 0; i < graph_size[u]; i++) {
            int v = graph[u][i];
            
            if (dist[u] + 1 > dist[v]) {
                dist[v] = dist[u] + 1;
                if (dist[v] > max_dist) max_dist = dist[v];
            }
 
            if (--deps[v] == 0) {
                S[s_ptr++] = v;
            }
        }
    }
 
    if (visited_count != V) return -1; // Cycle
    return max_dist;
}
 
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
 
    freopen("labin.txt", "r", stdin); freopen("labout.txt", "w", stdout);
 
    int V, P; cin >> V >> P;
 
    for (int i = 0; i < P; i++) {
        int u, v;
        cin >> u >> v;
        
        graph[u][graph_size[u]++] = v;
        deps[v]++;
    }
 
    cout << kahn(V);
}