#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("congain.txt", "r", stdin);
  freopen("congaout.txt", "w", stdout);
  int n, k;
  scanf("%d %d", &n, &k);
  vector<int> h(n);
  for (auto &x : h)
    scanf("%d", &x);

  int M = *max_element(h.begin(), h.begin() + k);
  int mn = *min_element(h.begin(), h.begin() + k);
  vector<pair<int, int>> fr;
  for (int i = k; i < n; i++)
    fr.push_back({h[i], i + 1});
  sort(fr.begin(), fr.end());

  vector<vector<pair<int, int>>> groups(k + 1);

  if (!fr.empty()) {
    int H = fr.back().first, L = fr.front().first;
    bool needTop = H > M, needBot = L < mn;
    int topg = 0, botg = 0;

    auto ctop = [&](int g) -> long long {
      if (g == 0)
        return max(0, H - h[0]);
      if (g == k)
        return max(0, H - h[k - 1]);
      return 2LL * max(0, H - max(h[g - 1], h[g]));
    };
    auto cbot = [&](int g) -> long long {
      if (g == 0)
        return max(0, h[0] - L);
      if (g == k)
        return max(0, h[k - 1] - L);
      return 2LL * max(0, min(h[g - 1], h[g]) - L);
    };
    auto joint = [&](int g) -> long long {
      if (g == 0 || g == k) {
        int e = (g == 0) ? h[0] : h[k - 1];
        long long up = max(0, H - e), dn = max(0, e - L);
        return up + dn + min(up, dn);
      }
      return ctop(g) + cbot(g);
    };

    if (needTop && needBot) {
      long long best = LLONG_MAX;
      for (int a = 0; a <= k; a++)
        for (int b = 0; b <= k; b++) {
          long long c = (a == b) ? joint(a) : ctop(a) + cbot(b);
          if (c < best) {
            best = c;
            topg = a;
            botg = b;
          }
        }
    } else if (needTop) {
      long long best = LLONG_MAX;
      for (int g = 0; g <= k; g++)
        if (ctop(g) < best) {
          best = ctop(g);
          topg = g;
        }
    } else if (needBot) {
      long long best = LLONG_MAX;
      for (int g = 0; g <= k; g++)
        if (cbot(g) < best) {
          best = cbot(g);
          botg = g;
        }
    }

    // internal gaps sorted by lower bound, with prefix-best by upper bound
    struct G {
      int lo, hi, g;
    };
    vector<G> gl;
    for (int g = 1; g < k; g++)
      gl.push_back({min(h[g - 1], h[g]), max(h[g - 1], h[g]), g});
    sort(gl.begin(), gl.end(),
         [](const G &x, const G &y) { return x.lo < y.lo; });
    vector<int> Ls, pref;
    int bi = -1;
    for (int i = 0; i < (int)gl.size(); i++) {
      Ls.push_back(gl[i].lo);
      if (bi == -1 || gl[i].hi > gl[bi].hi)
        bi = i;
      pref.push_back(bi);
    }

    for (auto &p : fr) {
      int v = p.first;
      if (v > M)
        groups[topg].push_back(p);
      else if (v < mn)
        groups[botg].push_back(p);
      else {
        int c = upper_bound(Ls.begin(), Ls.end(), v) - Ls.begin();
        if (c == 0)
          groups[0].push_back(p); // only when k == 1, v == h[0]
        else
          groups[gl[pref[c - 1]].g].push_back(p);
      }
    }
  }

  vector<int> seq;
  seq.reserve(n);
  for (int g = 0; g <= k; g++) {
    auto &grp = groups[g];
    sort(grp.begin(), grp.end());
    if (!grp.empty()) {
      int lo = grp.front().first, hi = grp.back().first;
      long long asc, desc;
      if (g == 0) {
        asc = abs(hi - h[0]);
        desc = abs(lo - h[0]);
      } else if (g == k) {
        asc = abs(lo - h[k - 1]);
        desc = abs(hi - h[k - 1]);
      } else {
        int a = h[g - 1], b = h[g];
        asc = abs(a - lo) + abs(hi - b);
        desc = abs(a - hi) + abs(lo - b);
      }
      if (desc < asc)
        reverse(grp.begin(), grp.end());
    }
    for (auto &p : grp)
      seq.push_back(p.second);
    if (g < k)
      seq.push_back(g + 1);
  }

  long long total = 0;
  for (int i = 0; i + 1 < n; i++)
    total += abs(h[seq[i] - 1] - h[seq[i + 1] - 1]);
  printf("%lld\n", total);
  for (int x : seq)
    printf("%d\n", x);
  return 0;
}
