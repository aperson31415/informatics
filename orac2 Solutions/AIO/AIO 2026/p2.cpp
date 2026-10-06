#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  
  // get smallest
  int smallval = INT_MAX, smallidx = -1;
  for(int i = 0; i < n; i++) {
    if(a[i] < smallval) {
      smallval = a[i];
      smallidx = i;
    }
  }

  // check
  int prev = -1;
  int res =  true;
  for(int i = smallidx; i < n; i++) {
    if(a[i] <= prev) res = false;
    prev = a[i];
  }

  for(int i = 0; i < smallidx; i++) {
    if(a[i] <= prev) res = false;
    prev = a[i];
  }

  if(res) cout << "YES";
  else cout << "NO";
}

