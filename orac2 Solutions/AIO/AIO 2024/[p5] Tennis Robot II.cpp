#include <bits/stdc++.h>
using namespace std;
#define int long long

int ceildiv(int a, int b) {
  return a/b + (a%b != 0);
}

signed main() {
  int n, m; cin >> n >> m;
  vector<int> x(n);
  for(int i = 0; i < n; i++) cin >> x[i];
  vector<pair<int, int>> instructions(m);
  for(int i = 0; i < m; i++) cin >> instructions[i].first >> instructions[i].second;
  
  for(int i = 0; i < m; i++) {
    instructions[i].first--;
    instructions[i].second--;
  }

  // Find net change per 'cycle'
  vector<int> rawnet_change(n, 0);
  vector<int> minnet_change(n, 0);
  for(int i = 0; i < m; i++) {
    rawnet_change[instructions[i].first]--;
    rawnet_change[instructions[i].second]++;
    minnet_change[instructions[i].first] = min(minnet_change[instructions[i].first], rawnet_change[instructions[i].first]);
    minnet_change[instructions[i].second] = min(minnet_change[instructions[i].second], rawnet_change[instructions[i].second]);
  }

  // Check if all are 0 - infinite, and none go under in first thingy
  bool infinite = true;
  for(int i = 0; i < n; i++) {
    if(rawnet_change[i] < 0) {
      infinite = false;
    }
  }

  for(int i = 0; i < n; i++) {
    if(rawnet_change[i] >= 0) {
      if(x[i] + minnet_change[i] < 0) infinite = false;
    }
  }


  if(infinite) {
    cout << "FOREVER";
    return 0;
  }

  // Find division thingy
  int full_cycles = 2e18 + 1;
  for(int i = 0; i < n; i++) {
    if(rawnet_change[i] >= 0) {
      if(x[i] + minnet_change[i] < 0) full_cycles = 0;
    } else {
      /*Check this bit!!!*/
      full_cycles = min(full_cycles, ceildiv(x[i]+minnet_change[i]+1, -rawnet_change[i]) );
    }
  }

  // Run last instruction loop thingy
  vector<int> newx(n);
  for(int i = 0; i < n; i++) {
    newx[i] = x[i] + full_cycles*rawnet_change[i];
  }

  int extra = 0;

  for(int i = 0; i < m; i++) {
    newx[instructions[i].first]--;
    newx[instructions[i].second]++;

    if(newx[instructions[i].first] < 0) {
      extra = i;
      break;
    }
  }

  // output
  cout << full_cycles*m + extra;
}
