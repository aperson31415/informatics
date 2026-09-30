#include <bits/stdc++.h>
using namespace std;
#define int long long

struct rest {int l, r;};

struct Lord {
  bool operator()(rest a, rest b) const {
    if(a.l != b.l) return a.l < b.l;
    return a.r < b.r;
  }
};

struct Rord {
  bool operator()(rest a, rest b) const {
    if(a.r != b.r) return a.r < b.r;
    else return a.l < b.l;
  }
};

signed main() {
  int n, m; cin >> n >> m;
  vector<int> a(n+1);
  for(int i = 1; i <= n; i++) cin >> a[i];
  set<rest, Lord> pairs;
  for(int i = 0; i < m; i++) {
    int li, ri; cin >> li >> ri;
    pairs.insert({li, ri});
  }

  // get cool

  vector<int> cool(n+1, -1);
  set<rest, Lord> lorder; set<rest, Rord> rorder; // min l -> max l, max r -> min r
  for(int i = 1; i <= n; i++) {
    while(!pairs.empty() && pairs.begin()->l == i) {
      lorder.insert(*(pairs.begin()));
      rorder.insert(*(pairs.begin()));
      pairs.erase(pairs.begin());
    }

    if(!lorder.empty()) {
      cool[i] = lorder.begin()->l;
    }

    while(!rorder.empty() && rorder.begin()->r == i) {
      lorder.erase(*(rorder.begin()));
      rorder.erase(rorder.begin());
    }
  }

  // do dp
  vector<int> dp(n+1, 0);
  vector<int> dpmax(n+1, 0);
  for(int i = 1; i <= n; i++) {
    if(cool[i] == -1) {
      dp[i] = a[i] + dpmax[i-1];
    } else {
      dp[i] = a[i] + dpmax[cool[i] - 1];
    }
    dpmax[i] = max(dp[i], dpmax[i-1]);
  }

  // output
  cout << dpmax[n];
}
