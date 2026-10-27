#include <bits/stdc++.h>
using namespace std;

pair<int, int> rangeIntersection(int a1, int b1, int a2, int b2) {
  if (a1 > b1)
    swap(a1, b1);
  if (a2 > b2)
    swap(a2, b2);

  int start = max(a1, a2);
  int end = min(b1, b2);

  if (start <= end)
    return {start, end};
  else
    return {-1, -1};
}

int ceildiv(int a, int b) { return a / b + (a % b != 0); }

int main() {
  int n, l;
  cin >> n >> l;
  vector<int> pos(n);
  for (int i = 0; i < n; i++)
    cin >> pos[i];
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];

  // Get ranges first
  vector<pair<int, int>> ranges;
  for (int i = 0; i < n - 1; i++) {
    int p1 = pos[a[i] - 1], p2 = pos[a[i + 1] - 1];
    // cout << i << ' ' << p1 << ' ' << p2 << '\n';
    if (p1 > p2) {
      // cout << ceildiv(p1+p2, 2) << '\n';
      ranges.push_back({ceildiv(p1 + p2, 2), l});
    } else {
      // cout << (p1+p2)/2 << '\n';
      ranges.push_back({1, (p1 + p2) / 2});
    }
  }

  for (int i = 0; i < n - 1; i++) {
    // cout << ranges[i].first << ' ' << ranges[i].second << '\n';
  }

  // Intersection of the ranges
  pair<int, int> curr = {1, l};
  for (int i = 0; i < n - 1; i++) {
    curr = rangeIntersection(ranges[i].first, ranges[i].second, curr.first,
                             curr.second);
  }

  cout << curr.first;
}
