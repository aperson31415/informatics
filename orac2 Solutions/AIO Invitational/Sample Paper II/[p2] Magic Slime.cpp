#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 2000005;
priority_queue<long long> pq[MAX_SIZE];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  cin >> N;

  int min_size = MAX_SIZE;
  int max_seen_size = 0;

  for (int i = 0; i < N; ++i) {
    long long a, s;
    cin >> a >> s;
    pq[a].push(s);
    if (a < min_size)
      min_size = a;
    if (a > max_seen_size)
      max_seen_size = a;
  }

  int current_max_size = max_seen_size;

  for (int size = min_size; size <= current_max_size; ++size) {
    while (pq[size].size() >= 2) {
      long long m1 = pq[size].top();
      pq[size].pop();
      long long m2 = pq[size].top();
      pq[size].pop();

      long long next_size = size + 1;
      pq[next_size].push(m1 + m2);

      if (next_size > current_max_size) {
        current_max_size = next_size;
      }
    }
  }

  while (current_max_size > 0 && pq[current_max_size].empty()) {
    current_max_size--;
  }

  cout << current_max_size << " " << pq[current_max_size].top();
}
