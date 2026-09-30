#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];

  int left_ptr = 0, right_ptr = n-1, left_sum = a[0], right_sum = a[n-1];
  int res = 0;

  while(true) {
    if(left_ptr >= n or right_ptr < 0 or left_ptr >= right_ptr) {
      break;
    }
    if(left_sum == right_sum) {
      left_ptr++;
      left_sum = a[left_ptr];
      right_ptr--;
      right_sum = a[right_ptr];
      continue;
    }
    if(left_sum > right_sum) {
      right_ptr--;
      right_sum += a[right_ptr];
      res++;
      continue;
    }
    if(right_sum > left_sum) {
      left_ptr++;
      left_sum += a[left_ptr];
      res++;
      continue;
    }
  }

  cout << res;
}
