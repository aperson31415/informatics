#include <bits/stdc++.h>
using namespace std;
#define int long long
 
signed main() {
  int n, q; cin >> n >> q;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  vector<pair<int, int>> queries(q);
  for(int i = 0; i < q; i++) cin >> queries[i].first >> queries[i].second;
  for(int i = 0; i < q; i++) queries[i].first--;
 
  vector<int> psum(n), ssum(n);
  psum[0] = a[0];
  for(int i = 1; i < n; i++) psum[i] = psum[i-1] + a[i];
  ssum[n-1] = a[n-1];
  for(int i = n - 2; i >= 0; i--) ssum[i] = ssum[i+1] + a[i];
 
  vector<int> req(n);
  req[0] = a[0];
  for(int i = 1; i < n; i++) req[i] = a[i] - psum[i-1];
 
  vector<int> pmax(n), smax(n);
  pmax[0] = req[0];
  for(int i = 1; i < n; i++) pmax[i] = max(pmax[i-1], req[i]);
  smax[n-1] = req[n-1];
  for(int i = n-2; i >= 0; i--) smax[i] = max(smax[i+1], req[i]);
 
  for(auto [x, b] : queries) {
    int ans = 0;
    if(x != 0) ans = max(ans, pmax[x-1]);
 
    if(x != 0) ans = max(ans, b - psum[x-1]);
    else ans = max(ans, b);
 
    if(x != n-1) ans = max(ans, smax[x+1] + a[x] - b);
 
    cout << ans << '\n';
  }
}
