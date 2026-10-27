#include "nav.h"
#include <vector>

static int N;

void init(int subtask, int n, int m, std::vector<int> A, std::vector<int> B) {
  N = n;
}

int findPrime() {
  int low = 0, high = N - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    int res = nav(mid);

    if (res == -1) {
      return mid;
    }

    if (res >= mid) {
      low = mid + 1; // Prime vertex is to the right
    } else {
      high = mid - 1; // Prime vertex is to the left
    }
  }
  return low;
}
