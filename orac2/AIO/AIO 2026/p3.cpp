#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k, d; cin >> n >> k >> d;
  vector<int> a(n + k);
  for(int i = k; i < n + k; i++) cin >> a[i];

  int window = 0;
  vector<int> taken(n + k, 0);

  for(int i = k; i < n+k; i++) {
    // calculate
    taken[i] = min(a[i], max(d - window, 0));
    // update
    if(i == n+k-1) continue;
    window += taken[i];
    window -= taken[i - k + 1];
  }

  int res = 0;
  for(int i = k; i < n+k; i++) res += taken[i];

  cout << res;
}

