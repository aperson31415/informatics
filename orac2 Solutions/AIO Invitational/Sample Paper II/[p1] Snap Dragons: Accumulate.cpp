#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, K;
  cin >> N >> K;

  vector<long long> a(N);
  for (int i = 0; i < N; ++i)
    cin >> a[i];

  vector<long long> positive_sums;
  long long current_sum = 0;

  for (int i = 0; i < N; ++i) {
    current_sum += a[i];
    if (i >= 1 && current_sum > 0) {
      positive_sums.push_back(current_sum);
    }
  }

  sort(positive_sums.rbegin(), positive_sums.rend());

  long long max_score = 0;
  int limit = min((int)positive_sums.size(), K);
  for (int i = 0; i < limit; ++i) {
    max_score += positive_sums[i];
  }

  cout << max_score;
}
