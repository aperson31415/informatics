#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> p(n);
  for(int i = 0; i < n; i++) cin >> p[i];
  int res = 0;
  for(int i = 0; i < n - 1; i++) {
    res = max(res, p[i + 1] - p[i]);
  }

  cout << res;
}

