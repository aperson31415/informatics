#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
typedef long long ll;
static const int NEG = -100000000, ST = 128;
static int W[101 * ST];
static int p[104], pos_[104], cin_[101][100], cc[101], bp[104], cout_[101][100],
    co[101];
static bool cm[101][128];
static double ltd[4096];
static u64 sd = 88172645463325252ULL;
static inline u64 rnd() {
  sd ^= sd << 13;
  sd ^= sd >> 7;
  sd ^= sd << 17;
  return sd * 0x2545F4914F6CDD1DULL;
}
static char buf[1 << 17];
static int n;
static ll cur, best;
static chrono::steady_clock::time_point t0;
static inline double el() {
  return chrono::duration<double>(chrono::steady_clock::now() - t0).count();
}

static ll U[110], V[110];
static int P[110];
static ll Acost[102][102];
// Hungarian algorithm; dummy city n joins the path's two ends into a cycle
static void hungarian() {
  int N = n + 1;
  const ll INF = (ll)4e18;
  ll(&a)[102][102] = Acost;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++) {
      int w = W[(i - 1) * ST + (j - 1)];
      a[i][j] = (w < 0) ? (ll)1e9 : -(ll)w;
    }
  vector<ll> u(N + 1, 0), v(N + 1, 0), minv(N + 1);
  vector<int> pp(N + 1, 0), way(N + 1, 0);
  vector<char> used(N + 1);
  for (int i = 1; i <= N; i++) {
    pp[0] = i;
    int j0 = 0;
    fill(minv.begin(), minv.end(), INF);
    fill(used.begin(), used.end(), 0);
    do {
      used[j0] = 1;
      int i0 = pp[j0], j1 = 0;
      ll delta = INF;
      for (int j = 1; j <= N; j++)
        if (!used[j]) {
          ll c = a[i0][j] - u[i0] - v[j];
          if (c < minv[j]) {
            minv[j] = c;
            way[j] = j0;
          }
          if (minv[j] < delta) {
            delta = minv[j];
            j1 = j;
          }
        }
      for (int j = 0; j <= N; j++) {
        if (used[j]) {
          u[pp[j]] += delta;
          v[j] -= delta;
        } else
          minv[j] -= delta;
      }
      j0 = j1;
    } while (pp[j0] != 0);
    do {
      int j1 = way[j0];
      pp[j0] = pp[j1];
      j0 = j1;
    } while (j0);
  }
  for (int i = 0; i <= N; i++) {
    U[i] = u[i];
    V[i] = v[i];
    P[i] = pp[i];
  }
}
static ll apBound;
static void buildCand(ll gap) { // keep edges with reduced cost <= gap
  for (int j = 0; j <= n; j++) {
    cc[j] = 0;
    co[j] = 0;
  }
  memset(cm, 0, sizeof cm);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      int w = W[i * ST + j];
      if (w < 0)
        continue;
      ll r = -(ll)w - U[i + 1] - V[j + 1];
      if (r <= gap) {
        cin_[j][cc[j]++] = i;
        cout_[i][co[i]++] = j;
        cm[i][j] = 1;
      }
    }
}
static void sa(double tEnd, double T0, double T1) {
  double T = T0, start = el(), span = max(1e-9, tEnd - start);
  u64 it = 0;
  while (true) {
    if ((it & 1023) == 0) {
      double t = el();
      if (t > tEnd)
        break;
      T = T0 * pow(T1 / T0, (t - start) / span);
    }
    it++;
    u64 r = rnd(), r2 = rnd();
    int i, j, k, u, v, sj, s0;
    if ((r & 31) == 0) { // insert a segment at the very front
      v = p[1];
      int vc = cc[v];
      if (!vc)
        continue;
      sj = cin_[v][(r2 >> 32) % (unsigned)vc];
      j = pos_[sj];
      if (j < 2)
        continue;
      i = 2 + (int)((r >> 8 & 0xffff) % (unsigned)(j - 1));
      s0 = p[i];
      u = n;
      k = 0;
    } else {
      i = 1 + (int)((r >> 20) % (unsigned)n);
      s0 = p[i];
      int L0 = p[i - 1];
      if (L0 == n) {
        j = i + (int)((r >> 8 & 0xffff) % (unsigned)(n - i));
      } else {
        int oc = co[L0];
        if (!oc)
          continue;
        int Rn = cout_[L0][(r >> 8 & 0xffff) % (unsigned)oc];
        j = pos_[Rn] - 1;
        if (j < i)
          continue;
      }
      sj = p[j];
      int ic = cc[s0];
      if (!ic)
        continue;
      u = cin_[s0][(r2 >> 32) % (unsigned)ic];
      k = pos_[u];
      if (k >= i - 1 && k <= j)
        continue;
      v = p[k + 1];
      if (v != n && !cm[sj][v])
        continue;
    }
    int L = p[i - 1], R = p[j + 1];
    int d = W[L * ST + R] + W[u * ST + s0] + W[sj * ST + v] - W[L * ST + s0] -
            W[sj * ST + R] - W[u * ST + v];
    if (d < 0 && (double)d < T * ltd[r2 & 4095])
      continue;
    if (k < i - 1) {
      rotate(p + k + 1, p + i, p + j + 1);
      for (int x = k + 1; x <= j; x++)
        pos_[p[x]] = x;
    } else {
      rotate(p + i, p + j + 1, p + k + 1);
      for (int x = i; x <= k; x++)
        pos_[p[x]] = x;
    }
    cur += d;
    if (cur > best) {
      best = cur;
      memcpy(bp, p, sizeof p);
    }
  }
}
// ---------- exact branch and bound (assignment-problem bound, subtour
// elimination) ----------
static int forcedRow[104], forcedCol[104];
static bool timeUp;
static ll bestCost;
static long long nodes;
static double bnbEnd;
static ll mvv[104];
static int wayv[104];
static char usedv[104];
static const ll BINF = (ll)1e9;
static inline ll costf(int i, int j) {
  int fr = forcedRow[i];
  if (fr >= 0)
    return j == fr ? Acost[i][j] : BINF;
  int fc = forcedCol[j];
  if (fc >= 0 && fc != i)
    return BINF;
  return Acost[i][j];
}
static void augment(int i, ll *u, ll *v, int *pp) {
  int N = n + 1;
  const ll INF = (ll)4e18;
  pp[0] = i;
  int j0 = 0;
  for (int j = 0; j <= N; j++) {
    mvv[j] = INF;
    usedv[j] = 0;
  }
  do {
    usedv[j0] = 1;
    int i0 = pp[j0], j1 = 0;
    ll delta = INF;
    for (int j = 1; j <= N; j++)
      if (!usedv[j]) {
        ll c = costf(i0, j) - u[i0] - v[j];
        if (c < mvv[j]) {
          mvv[j] = c;
          wayv[j] = j0;
        }
        if (mvv[j] < delta) {
          delta = mvv[j];
          j1 = j;
        }
      }
    for (int j = 0; j <= N; j++) {
      if (usedv[j]) {
        u[pp[j]] += delta;
        v[j] -= delta;
      } else
        mvv[j] -= delta;
    }
    j0 = j1;
  } while (pp[j0] != 0);
  do {
    int j1 = wayv[j0];
    pp[j0] = pp[j1];
    j0 = j1;
  } while (j0);
}
static void bnb(const ll *u, const ll *v, const int *pp) {
  if (timeUp)
    return;
  nodes++;
  if ((nodes & 15) == 0 && el() > bnbEnd) {
    timeUp = true;
    return;
  }
  int N = n + 1;
  int nxt[104];
  for (int j = 1; j <= N; j++)
    nxt[pp[j]] = j;
  bool vis[104];
  for (int i = 1; i <= N; i++)
    vis[i] = 0;
  int cycles = 0, bestStart = -1, bestFree = 1 << 30;
  for (int i = 1; i <= N; i++)
    if (!vis[i]) {
      cycles++;
      int x = i, fr = 0;
      do {
        vis[x] = 1;
        if (forcedRow[x] < 0)
          fr++;
        x = nxt[x];
      } while (x != i);
      if (fr < bestFree) {
        bestFree = fr;
        bestStart = i;
      }
    }
  if (cycles == 1) { // a single cycle = a valid trip
    ll Wt = 0;
    int x = nxt[N];
    int cnt = 0;
    int path[104];
    while (x != N) {
      path[cnt++] = x - 1;
      x = nxt[x];
    }
    for (int t = 0; t + 1 < cnt; t++)
      Wt += W[path[t] * ST + path[t + 1]];
    if (Wt > best) {
      best = Wt;
      bestCost = -Wt;
      bp[0] = bp[n + 1] = n;
      for (int t = 0; t < cnt; t++)
        bp[t + 1] = path[t];
    }
    return;
  }
  if (bestFree == 0)
    return;
  int ei[104], ej[104], m = 0;
  {
    int x = bestStart;
    do {
      if (forcedRow[x] < 0) {
        ei[m] = x;
        ej[m] = nxt[x];
        m++;
      }
      x = nxt[x];
    } while (x != bestStart);
  }
  for (int k = 0; k < m; k++) {
    int ik = ei[k], jk = ej[k];
    ll sv = Acost[ik][jk];
    Acost[ik][jk] = BINF; // child: forbid edge k, force edges 0..k-1
    ll u2[104], v2[104];
    int p2[104];
    memcpy(u2, u, sizeof(ll) * (N + 1));
    memcpy(v2, v, sizeof(ll) * (N + 1));
    memcpy(p2, pp, sizeof(int) * (N + 1));
    p2[jk] = 0;
    augment(ik, u2, v2, p2);
    ll lb = 0;
    bool bad = false;
    for (int j = 1; j <= N; j++) {
      ll c = costf(p2[j], j);
      if (c >= BINF) {
        bad = true;
        break;
      }
      lb += c;
    }
    if (!bad && lb < bestCost)
      bnb(u2, v2, p2);
    Acost[ik][jk] = sv;
    if (timeUp)
      break;
    forcedRow[ik] = jk;
    forcedCol[jk] = ik;
  }
  for (int k = 0; k < m; k++) {
    forcedRow[ei[k]] = -1;
    forcedCol[ej[k]] = -1;
  }
}
int main() {
  t0 = chrono::steady_clock::now();
  size_t len = fread(buf, 1, sizeof buf - 1, stdin);
  buf[len] = 0;
  char *c = buf;
  auto readInt = [&]() -> int {
    while (*c && *c != '-' && (*c < '0' || *c > '9'))
      c++;
    int s = 1;
    if (*c == '-') {
      s = -1;
      c++;
    }
    int x = 0;
    while (*c >= '0' && *c <= '9')
      x = x * 10 + *c++ - '0';
    return x * s;
  };
  n = readInt();
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      int v = readInt();
      W[i * ST + j] = (v < 0) ? NEG : v;
    }
  for (int i = 0; i <= n; i++) {
    W[n * ST + i] = 0;
    W[i * ST + n] = 0;
  }
  W[n * ST + n] = NEG;
  vector<int> q;
  q.push_back(0);
  for (int x = 1; x < n; x++) {
    if (W[x * ST + q[0]] >= 0) {
      q.insert(q.begin(), x);
      continue;
    }
    if (W[q.back() * ST + x] >= 0) {
      q.push_back(x);
      continue;
    }
    for (size_t i = 0; i + 1 < q.size(); i++)
      if (W[q[i] * ST + x] >= 0 && W[x * ST + q[i + 1]] >= 0) {
        q.insert(q.begin() + i + 1, x);
        break;
      }
  }
  p[0] = p[n + 1] = n;
  for (int i = 0; i < n; i++) {
    p[i + 1] = q[i];
    pos_[q[i]] = i + 1;
  }
  cur = 0;
  for (int i = 1; i < n; i++)
    cur += W[p[i] * ST + p[i + 1]];
  best = cur;
  memcpy(bp, p, sizeof p);
  const double TL = 0.95, t1 = 0.05, bbEnd = 0.6;
  if (n >= 3) {
    for (int i = 0; i < 4096; i++)
      ltd[i] = log((i + 0.5) / 4096.0);
    hungarian();
    ll ap = 0;
    for (int j = 1; j <= n + 1; j++) {
      int i = P[j];
      ap += W[(i - 1) * ST + (j - 1)];
    }
    apBound = ap;
    // quick annealing on the full graph, just to get a good starting incumbent
    for (int j = 0; j < n; j++) {
      cc[j] = 0;
      co[j] = 0;
    }
    memset(cm, 0, sizeof cm);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (W[i * ST + j] >= 0 && i != j) {
          cin_[j][cc[j]++] = i;
          cout_[i][co[i]++] = j;
          cm[i][j] = 1;
        }
    cc[n] = 0;
    co[n] = 0;
    sa(t1, 40000, 5000);
    // exact search
    ll u0[104], v0[104];
    int p0[104];
    for (int i = 0; i <= n + 1; i++) {
      u0[i] = U[i];
      v0[i] = V[i];
      p0[i] = P[i];
    }
    for (int i = 0; i < 104; i++) {
      forcedRow[i] = -1;
      forcedCol[i] = -1;
    }
    bestCost = -best;
    bnbEnd = bbEnd;
    timeUp = false;
    nodes = 0;
    bnb(u0, v0, p0);
    if (timeUp) { // safety net: anneal on the reduced graph with the remaining
                  // time
      memcpy(p, bp, sizeof p);
      for (int x = 1; x <= n; x++)
        pos_[p[x]] = x;
      cur = best;
      buildCand(max(0LL, apBound - best));
      sa(TL, 20000, 4000);
    }
  }
  string out;
  for (int i = 1; i <= n; i++) {
    out += to_string(bp[i] + 1);
    out += '\n';
  }
  fputs(out.c_str(), stdout);
}
