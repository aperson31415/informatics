%:include <bits/stdc++.h>
%:include <immintrin.h>
%:pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

#define fio(in,out) freopen(in,"r",stdin); freopen(out,"w",stdout)
 
vector<vector<int>> adj;
vector<vector<bool>> visiteda, visitedb;
vector<vector<int>> dista, distb;
 
struct node {
    int num, parity;
};
 
void bfsa(int s, int parity) {
    queue<node> q;
    visiteda[s][parity] = true;
    dista[s][parity] = 0;
    q.push({s, parity});
    while(!q.empty()) {
        node top = q.front(); q.pop();
        for(int u : adj[top.num]) {
            if (visiteda[u][1-top.parity]) continue;
            visiteda[u][1-top.parity] = true;
            dista[u][1-top.parity] = dista[top.num][top.parity]+1;
            q.push({u, 1-top.parity});
        }
    }
}

void bfsb(int s, int parity) {
    queue<node> q;
    visitedb[s][parity] = true;
    distb[s][parity] = 0;
    q.push({s, parity});
    while(!q.empty()) {
        node top = q.front(); q.pop();
        for(int u : adj[top.num]) {
            if (visitedb[u][1-top.parity]) continue;
            visitedb[u][1-top.parity] = true;
            distb[u][1-top.parity] = distb[top.num][top.parity]+1;
            q.push({u, 1-top.parity});
        }
    }
}
 
int io = [](){cin.tie(0)->sync_with_stdio(0);return 0;}();
int main() {
  fio("frogsin.txt", "frogsout.txt");

  int p, j; cin >> p >> j;
  int sa, sb; cin >> sa >> sb;
  sa--; sb--;
  adj.resize(p);
  visiteda.resize(p, {false, false}); visitedb.resize(p, {false, false});
  dista.resize(p, {-1, -1}); distb.resize(p, {-1, -1});
  
  for(int i = 0; i < j; i++) {
    int p1, p2; cin >> p1 >> p2;
    p1--; p2--;
    adj[p1].push_back(p2);
    adj[p2].push_back(p1);
  }

  bfsa(sa, 0);
  bfsb(sb, 0);

  int res = INT_MAX;
  int res_holder = -1;
  bool together = false;

  for(int i = 0; i < p; i++) {
    if(visiteda[i][0] and visitedb[i][0]) {
      together = true;
      if(max(dista[i][0], distb[i][0]) < res) {
        res = max(dista[i][0], distb[i][0]);
        res_holder = i;
      }
    }
    if(visiteda[i][1] and visitedb[i][1]) {
      together = true;
      if(max(dista[i][1], distb[i][1]) < res) {
        res = max(dista[i][1], distb[i][1]);
        res_holder = i;
      }
    }
  }

  if(not together) cout << "Broken heart";
  else cout << res << ' ' << res_holder+1;
}
