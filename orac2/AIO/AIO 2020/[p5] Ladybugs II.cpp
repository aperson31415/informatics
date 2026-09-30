#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k, q; cin >> n >> k >> q;
  vector<int> p(n);
  for(int i = 0; i < n; i++) cin >> p[i];
  vector<int> d(q);
  for(int i = 0; i < q; i++) cin >> d[i];

  for(int i = 0; i < q; i++) {
    int res = INT_MAX; // or a large enough value
    int target = d[i];
    
    // Find first element >= target
    auto it = lower_bound(p.begin(), p.end(), target);
    int idx = distance(p.begin(), it);

    // Check all possible window start positions j that could cover target
    int start_min = max(0, idx - k);
    int start_max = min(n - k, idx);

    int ans = 2e9; // Safe large number instead of INT_MAX overflow
    for(int j = start_min; j <= start_max; j++) {
      int left_num = p[j];
      int right_num = p[j + k - 1];
      int span = right_num - left_num;
      int cost = span + min(abs(target - left_num), abs(target - right_num));
      ans = min(ans, cost);
    }

    cout << ans << ' ';
  }
}
