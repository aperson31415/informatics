#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, h; cin >> n >> h;
  vector<pair<int, int>> a(n + 1);
  for(int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
  a[n] = {0, 0};

  // Run 0/1 DP
  set<int> prev = {0}; vector<int> curr = {0};
  for(int i = 0; i < n; i++) {
    for(int elem : prev) {
      if(elem + a[i].first <= h) curr.push_back(elem + a[i].first);
      if(elem + a[i].second <= h) curr.push_back(elem + a[i].second);
    }
    for(auto elem : curr) {
      prev.insert(elem);
    }
    curr = {0};
  }

  int res = 0;
  for(int elem : prev) {
    res = max(res, elem);
  }

  cout << res;
}
