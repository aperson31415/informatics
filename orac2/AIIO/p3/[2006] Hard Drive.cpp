#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
  //freopen("drivein.txt","r",stdin); freopen("driveout.txt", "w",stdout);
  int n, m; cin >> n >> m;
  if(n == 0) {
    cout << 1%m;
    return 0;
  }
  if(n == 1) {
    cout << 2%m;
    return 0;
  }

  vector<int> dp(n+1);
  dp[0] = 1%m; dp[1] = 2%m;

  for(int i = 2; i <= n; i++) {
    dp[i] = (1 + (dp[i-1]*dp[i-1])%m + (((dp[i-1]*dp[i-2])%m)*dp[i-2])%m - ((dp[i-2]*dp[i-2])%m)*((dp[i-2]*dp[i-2])%m))%m;
  }

  cout << (dp[n] + m)%m;
}
