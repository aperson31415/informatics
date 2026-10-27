#include <bits/stdc++.h>
using namespace std;

struct Tourist {
  long long s, e;
};

bool check(long long K, int n, const vector<Tourist> &tourists) {
  if (K == 0)
    return true;

  vector<Tourist> t = tourists;
  sort(t.begin(), t.end(), [](const Tourist &a, const Tourist &b) {
    if (a.s != b.s)
      return a.s < b.s;
    return a.e < b.e;
  });

  priority_queue<pair<long long, long long>, vector<pair<long long, long long>>,
                 greater<pair<long long, long long>>>
      pq;

  int idx = 0;
  long long current_time = t[0].s;
  vector<long long> rem(n, K);

  while (idx < n || !pq.empty()) {
    if (pq.empty()) {
      if (current_time < t[idx].s) {
        current_time = t[idx].s;
      }
    }

    while (idx < n && t[idx].s <= current_time) {
      pq.push({t[idx].e, idx});
      idx++;
    }

    if (pq.empty())
      continue;

    auto top_elem = pq.top();
    pq.pop();

    long long deadline = top_elem.first;
    long long id = top_elem.second;

    long long next_release = (idx < n) ? t[idx].s : 2e18;
    long long max_days_by_deadline = deadline - current_time + 1;
    long long max_days_by_next = next_release - current_time;

    if (max_days_by_deadline <= 0)
      return false;

    long long m = min({rem[id], max_days_by_deadline, max_days_by_next});
    if (m <= 0)
      return false;

    rem[id] -= m;
    current_time += m;

    if (rem[id] > 0) {
      pq.push({deadline, id});
    }
  }

  for (int i = 0; i < n; ++i) {
    if (rem[i] > 0)
      return false;
  }

  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  vector<Tourist> tourists(n);
  long long max_possible = 2e12;
  for (int i = 0; i < n; ++i) {
    cin >> tourists[i].s >> tourists[i].e;
    max_possible = min(max_possible, tourists[i].e - tourists[i].s + 1);
  }

  long long low = 0, high = max_possible, ans = 0;
  while (low <= high) {
    long long mid = low + (high - low) / 2;
    if (check(mid, n, tourists)) {
      ans = mid;
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  cout << ans;
}
