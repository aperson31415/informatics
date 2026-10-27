#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int L;
vector<ll> dA[2], dB[2]; // [which] slope-coef diff, const diff

void addPiece(int w, ll l, ll r, int s, ll c, ll fv) {
  if (l < 0)
    l = 0;
  if (r > L)
    r = L;
  if (l > r)
    return;
  ll a = -s, b = fv - c;
  if (a == 0) {
    if (b <= 0)
      return;
  } else if (a == 1)
    l = max(l, -b + 1);
  else
    r = min(r, b - 1);
  if (l > r)
    return;
  dA[w][l] += a;
  dA[w][r + 1] -= a;
  dB[w][l] += b;
  dB[w][r + 1] -= b;
}

void addTrip(int w, ll x, ll sl, ll sr, ll fv) {
  // left side, p in [0, x]
  if (sl != -1) {
    addPiece(w, 0, sl, -1, x, fv);
    if (sl < x) {
      if (sr != -1) {
        ll m = sr - x + sl;
        addPiece(w, sl + 1, min(x, m), 0, x - sl, fv);
        addPiece(w, max(sl + 1, m + 1), x, -1, sr, fv);
      } else
        addPiece(w, sl + 1, x, 0, x - sl, fv);
    }
  } else
    addPiece(w, 0, x, -1, sr, fv);
  // right side, p in [x+1, L]
  if (sr != -1) {
    addPiece(w, max(sr, x + 1), L, 1, -x, fv);
    if (sr > x) {
      if (sl != -1) {
        ll m = sr - x + sl;
        addPiece(w, x + 1, min(sr - 1, m), 1, -sl, fv);
        addPiece(w, max(x + 1, m + 1), sr - 1, 0, sr - x, fv);
      } else
        addPiece(w, x + 1, sr - 1, 0, sr - x, fv);
    }
  } else
    addPiece(w, x + 1, L, 1, -sl, fv);
}

int main() {
  int N;
  scanf("%d %d", &N, &L);
  vector<char> hasA(L + 1, 0), hasB(L + 1, 0);
  int cntB = 0;
  for (int i = 0; i < N; i++) {
    int b, r;
    scanf("%d %d", &b, &r);
    if (r == 1)
      hasA[b] = 1;
    else {
      hasB[b] = 1;
      cntB++;
    }
  }
  vector<int> pA(L + 1), nA(L + 1), pB(L + 1), nB(L + 1);
  for (int i = 0; i <= L; i++) {
    pA[i] = hasA[i] ? i : (i ? pA[i - 1] : -1);
    pB[i] = hasB[i] ? i : (i ? pB[i - 1] : -1);
  }
  for (int i = L; i >= 0; i--) {
    nA[i] = hasA[i] ? i : (i < L ? nA[i + 1] : -1);
    nB[i] = hasB[i] ? i : (i < L ? nB[i + 1] : -1);
  }
  for (int w = 0; w < 2; w++) {
    dA[w].assign(L + 3, 0);
    dB[w].assign(L + 3, 0);
  }

  int T;
  scanf("%d", &T);
  ll base = 0;
  bool has3 = false;
  for (int j = 0; j < T; j++) {
    int x, s;
    scanf("%d %d", &x, &s);
    if (s == 2) {
      int al = pA[x], ar = nA[x];
      ll d = LLONG_MAX;
      if (al != -1)
        d = min(d, (ll)x - al);
      if (ar != -1)
        d = min(d, (ll)ar - x);
      base += 1 + 2 * d;
      // add to river 1: new(p) = |x-p|
      addPiece(0, 0, x, -1, x, d);
      addPiece(0, x + 1, L, 1, -x, d);
    } else {
      has3 = true;
      ll f;
      if (cntB == 0)
        f = L + 1;
      else {
        f = LLONG_MAX;
        int as[2] = {pA[x], nA[x]}, bs[2] = {pB[x], nB[x]};
        for (int i = 0; i < 2; i++)
          for (int k = 0; k < 2; k++) {
            if (as[i] == -1 || bs[k] == -1)
              continue;
            int mx = max({x, as[i], bs[k]}), mn = min({x, as[i], bs[k]});
            f = min(f, (ll)(mx - mn));
          }
      }
      base += 2 + 2 * f;
      if (cntB > 0)
        addTrip(0, x, pB[x], nB[x], f); // new bridge on river 1, S = B
      addTrip(1, x, pA[x], nA[x], f);   // new bridge on river 2, S = A
    }
  }

  ll ans = LLONG_MAX;
  for (int w = 0; w < 2; w++) {
    if (w == 0 && cntB == 0 && has3)
      continue;
    ll ca = 0, cb = 0, best = 0;
    for (int p = 0; p <= L; p++) {
      ca += dA[w][p];
      cb += dB[w][p];
      best = max(best, ca * p + cb);
    }
    ans = min(ans, base - 2 * best);
  }
  printf("%lld\n", ans);
  return 0;
}
