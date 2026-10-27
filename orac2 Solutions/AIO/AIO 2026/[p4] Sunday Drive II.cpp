// might not work, just a thingy ig
 
#include <bits/stdc++.h>
using namespace std;
 
int main() {
  int n; cin >> n;
  vector<int> x(n);
  for(int i = 0; i < n; i++) cin >> x[i];
 
  vector<int> maxpos(n);
 
  maxpos[n-1] = x[n-1];
  for(int i = n-2; i >= 0; i--) maxpos[i] = min(x[i], maxpos[i+1]+1);
 
  maxpos[0] = min(maxpos[0], 1);
  for(int i = 1; i < n; i++) maxpos[i] = min(maxpos[i-1]+1, maxpos[i]);
 
  int res = 0;
  for(int i = 0; i < n; i++) res += maxpos[i];
 
  cout << res;
}
