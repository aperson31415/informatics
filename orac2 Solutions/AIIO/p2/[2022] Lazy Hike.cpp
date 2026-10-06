#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<vector<pair<int, int>>> adj; //node, weight
vector<int> dist;
vector<bool> processed;

template<typename T>
void dijkstra(T start_node){
  priority_queue<pair<int,T>,vector<pair<int, T>>,greater<pair<int,T>>>q;
  dist[start_node]=0;
  q.push({0,start_node}); //{dist , node}
  while(!q.empty()){
    T a =q.top().second;
    q.pop();
    if(processed[a]) continue;
    processed[a]= true;
    for(auto u:adj[a]){
      int b=u.first;
      T w=u.second;
      if(dist[a]+w<dist[b]){
        dist[b]=dist[a]+w;
        q.push({dist[b],b});
      }
    }
  }
}

signed main() {
  int n, a, b; cin >> n >> a >> b;
  vector<int> h(n);
  for(int i = 0; i < n; i++) cin >> h[i];
  int m; cin >> m;

  adj.resize(n);
  dist.resize(n+1, LLONG_MAX);
  processed.resize(n+1, false);
  for(int i = 0; i < m; i++) {
    int ui, vi; cin >> ui >> vi;
    ui--; vi--;
    if(h[ui] > h[vi]) {
      adj[ui].push_back({vi, h[ui]-h[vi]});
      adj[vi].push_back({ui, 0});
    } else {
      adj[vi].push_back({ui, h[vi]-h[ui]});
      adj[ui].push_back({vi, 0});
    }
  }

  dijkstra(0);

  int res = 0;
  for(int i = 0; i < n; i++) {
    if(dist[i] <= b and dist[i] + h[i] - h[0] <= a) {
      res++;
    }
  }

  cout << res;
}
