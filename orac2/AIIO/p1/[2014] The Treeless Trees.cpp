#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
  int n; cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];

  int res = a[0];
  for(int i = 1; i < n; i++) res += max(0ll, a[i] - a[i-1]);
  cout << res;
}
