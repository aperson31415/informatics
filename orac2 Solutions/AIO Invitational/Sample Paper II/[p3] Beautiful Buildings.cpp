#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  scanf("%d", &n);
  vector<int> A(n), B(n);
  for (auto &x : A)
    scanf("%d", &x);
  for (auto &x : B)
    scanf("%d", &x);

  // upRight[v]   = right end of the up segment (Ai < Bi) that starts at v, 0 if
  // none downRight[v] = right end of the down segment (Ai > Bi) that starts at
  // v, 0 if none
  vector<int> upRight(n + 2, 0), downRight(n + 2, 0);

  long long total = 0;
  for (int i = 0; i < n; i++) {
    total += llabs((long long)A[i] - B[i]);
    if (A[i] < B[i])
      upRight[A[i]] = B[i];
    else if (A[i] > B[i])
      downRight[B[i]] = A[i];
  }

  int bestUp = 0, bestDown = 0; // largest right endpoint seen so far, per type
  long long bestOverlap = 0;

  for (int v = 1; v <= n; v++) {
    if (upRight[v]) {
      int r = upRight[v];
      if (bestDown)
        bestOverlap = max(bestOverlap, (long long)min(r, bestDown) - v);
      bestUp = max(bestUp, r);
    }
    if (downRight[v]) {
      int r = downRight[v];
      if (bestUp)
        bestOverlap = max(bestOverlap, (long long)min(r, bestUp) - v);
      bestDown = max(bestDown, r);
    }
  }

  printf("%lld\n", total - 2 * bestOverlap);
}
