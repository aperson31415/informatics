#include <bits/stdc++.h>
using namespace std;
static const int MAXN = 1005;
int n;
int posr[MAXN];
static int16_t Qt[MAXN][MAXN];
static int F[2][MAXN][MAXN];
static int8_t Ctype[2][MAXN][MAXN];
static int16_t Cm[2][MAXN][MAXN];

const int LMAX = 7;
unordered_map<long long, int> leafId[LMAX + 1];
vector<vector<int>> leafPerm[LMAX + 1];
vector<array<int, LMAX + 2>> leafD[LMAX + 1];
long long enc(const vector<int> &v) {
  long long h = 0;
  for (int x : v)
    h = h * 9 + x;
  return h;
}
void buildLeaf() {
  leafPerm[0].push_back({});
  leafId[0][0] = 0;
  leafD[0].push_back({});
  leafD[0][0].fill(0);
  for (int r = 1; r <= LMAX; r++) {
    vector<int> p(r);
    iota(p.begin(), p.end(), 1);
    do {
      leafId[r][enc(p)] = leafPerm[r].size();
      leafPerm[r].push_back(p);
    } while (next_permutation(p.begin(), p.end()));
    int cnt = leafPerm[r].size();
    const int INF = 1e9;
    leafD[r].assign(cnt, array<int, LMAX + 2>());
    for (auto &a : leafD[r])
      a.fill(INF);
    vector<array<int, LMAX + 1>> mid(cnt);
    for (int i = 0; i < cnt; i++) {
      auto &pm = leafPerm[r][i];
      for (int q = 0; q < r; q++) {
        vector<int> np;
        np.push_back(pm[q]);
        for (int j = 0; j < r; j++)
          if (j != q)
            np.push_back(pm[j]);
        mid[i][q] = leafId[r][enc(np)];
        if (pm[q] == 1) {
          vector<int> rest;
          for (int j = 0; j < r; j++)
            if (j != q)
              rest.push_back(pm[j] - 1);
          leafD[r][i][q] = 1 + leafD[r - 1][leafId[r - 1][enc(rest)]][0];
        }
      }
    }
    bool ch = true;
    while (ch) {
      ch = false;
      for (int i = 0; i < cnt; i++) {
        auto &arr = leafD[r][i];
        for (int q = 0; q <= r; q++) {
          int best = arr[q];
          if (q < r) {
            best = min(best, 1 + arr[q + 1]);
            best = min(best, 1 + leafD[r][mid[i][q]][q + 1]);
          }
          if (q > 0)
            best = min(best, 1 + arr[q - 1]);
          if (q != 0)
            best = min(best, 1 + arr[0]);
          if (best < arr[q]) {
            arr[q] = best;
            ch = true;
          }
        }
      }
    }
  }
}
int Lleaf = LMAX;
int leafCost(int a, int k, int o) {
  vector<pair<int, int>> v;
  for (int r = a; r < a + k; r++)
    v.push_back({posr[r], r});
  sort(v.begin(), v.end());
  if (o)
    reverse(v.begin(), v.end());
  vector<int> rk(k);
  for (int i = 0; i < k; i++)
    rk[i] = v[i].second - a + 1;
  return leafD[k][leafId[k][enc(rk)]][0];
}
static int spmx[11][MAXN], spmn[11][MAXN];
int lg2[MAXN];
void buildSparse() {
  for (int i = 2; i < MAXN; i++)
    lg2[i] = lg2[i / 2] + 1;
  for (int i = 1; i <= n; i++) {
    spmx[0][i] = spmn[0][i] = posr[i];
  }
  for (int j = 1; j < 11; j++)
    for (int i = 1; i + (1 << j) - 1 <= n; i++) {
      spmx[j][i] = max(spmx[j - 1][i], spmx[j - 1][i + (1 << (j - 1))]);
      spmn[j][i] = min(spmn[j - 1][i], spmn[j - 1][i + (1 << (j - 1))]);
    }
}
inline int qmx(int l, int r) {
  int j = lg2[r - l + 1];
  return max(spmx[j][l], spmx[j][r - (1 << j) + 1]);
}
inline int qmn(int l, int r) {
  int j = lg2[r - l + 1];
  return min(spmn[j][l], spmn[j][r - (1 << j) + 1]);
}
inline int fidx(int a, int b, int r) {
  int p = posr[r];
  return Qt[p][b - 1] - Qt[p][a - 1];
}
vector<int> st;
string ops;
void leafGen(int k) {
  vector<int> sorted_(st.begin(), st.begin() + k);
  sort(sorted_.begin(), sorted_.end());
  vector<int> cur(k);
  for (int i = 0; i < k; i++)
    cur[i] = lower_bound(sorted_.begin(), sorted_.end(), st[i]) -
             sorted_.begin() + 1;
  int p = 0;
  int r = k;
  while (r > 0) {
    int id = leafId[r][enc(cur)];
    int d = leafD[r][id][p];
    if (p < r && cur[p] == 1) {
      vector<int> rest;
      for (int j = 0; j < r; j++)
        if (j != p)
          rest.push_back(cur[j] - 1);
      if (d == 1 + leafD[r - 1][leafId[r - 1][enc(rest)]][0]) {
        ops += 'T';
        st.erase(st.begin() + p);
        cur = rest;
        r--;
        p = 0;
        continue;
      }
    }
    if (p < r && d == 1 + leafD[r][id][p + 1]) {
      ops += 'N';
      p++;
      continue;
    }
    if (p < r) {
      vector<int> np;
      np.push_back(cur[p]);
      for (int j = 0; j < r; j++)
        if (j != p)
          np.push_back(cur[j]);
      if (d == 1 + leafD[r][leafId[r][enc(np)]][p + 1]) {
        ops += 'M';
        int v2 = st[p];
        st.erase(st.begin() + p);
        st.insert(st.begin(), v2);
        cur = np;
        p++;
        continue;
      }
    }
    if (p > 0 && d == 1 + leafD[r][id][p - 1]) {
      ops += 'P';
      p--;
      continue;
    }
    if (p != 0 && d == 1 + leafD[r][id][0]) {
      ops += 'R';
      p = 0;
      continue;
    }
    assert(false);
  }
}
void gen(int a, int k, int o) {
  if (k == 0)
    return;
  int ty = Ctype[o][a][k];
  int m = Cm[o][a][k];
  if (ty == 0) {
    leafGen(k);
    return;
  }
  if (ty == 1) {
    int last = -1;
    for (int i = 0; i < k; i++)
      if (st[i] < a + m)
        last = i;
    for (int p = 0; p <= last; p++) {
      if (st[p] < a + m) {
        int v = st[p];
        st.erase(st.begin() + p);
        st.insert(st.begin(), v);
        ops += 'M';
      } else
        ops += 'N';
    }
    ops += 'R';
    gen(a, m, 1 - o);
    gen(a + m, k - m, o);
  } else {
    int ia = -1;
    for (int i = 0; i < k; i++)
      if (st[i] == a)
        ia = i;
    for (int p = 0; p < ia; p++) {
      if (st[p] > a && st[p] < a + 1 + m) {
        int v = st[p];
        st.erase(st.begin() + p);
        st.insert(st.begin(), v);
        ops += 'M';
      } else
        ops += 'N';
    }
    ops += 'T';
    for (int i = 0; i < (int)st.size(); i++)
      if (st[i] == a) {
        st.erase(st.begin() + i);
        break;
      }
    if (m > 0)
      gen(a + 1, m, 1 - o);
    gen(a + 1 + m, k - 1 - m, o);
  }
}
int main() {
  if (scanf("%d", &n) != 1)
    return 0;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    if (scanf("%d", &arr[i]) != 1)
      return 0;
    posr[arr[i]] = i;
  }
  buildLeaf();
  buildSparse();
  for (int p = 0; p <= n; p++) {
    Qt[p][0] = 0;
    for (int x = 1; x <= n; x++)
      Qt[p][x] = Qt[p][x - 1] + (posr[x] < p ? 1 : 0);
  }
  const int INF = 1e9;
  for (int o = 0; o < 2; o++)
    for (int a = 0; a < MAXN; a++)
      F[o][a][0] = 0;
  for (int k = 1; k <= n; k++) {
    for (int a = 1; a + k - 1 <= n; a++) {
      int b = a + k;
      for (int o = 0; o < 2; o++) {
        int best = INF;
        int bt = -1, bm = 0;
        if (k <= Lleaf) {
          int c = leafCost(a, k, o);
          if (c < best) {
            best = c;
            bt = 0;
          }
        }
        {
          int lo = 1, hi = k - 1;
          if (k > 24) {
            int w = max(5, k / 20);
            lo = max(1, k / 2 - w);
            hi = min(k - 1, k / 2 + w);
          }
          for (int m = lo; m <= hi; m++) {
            int last;
            if (!o) {
              int mp = qmx(a, a + m - 1);
              last = Qt[mp][b - 1] - Qt[mp][a - 1];
            } else {
              int mp = qmn(a, a + m - 1);
              last = k - 1 - (Qt[mp][b - 1] - Qt[mp][a - 1]);
            }
            int c = last + 2 + F[1 - o][a][m] + F[o][a + m][k - m];
            if (c < best) {
              best = c;
              bt = 1;
              bm = m;
            }
          }
        }
        {
          int ia = fidx(a, b, a);
          if (o)
            ia = k - 1 - ia;
          for (int m = 0; m <= min(k - 1, 16); m++) {
            if (m > 0) {
              int ir = fidx(a, b, a + m);
              if (o)
                ir = k - 1 - ir;
              if (ir >= ia)
                break;
            }
            int c = ia + 1 + (m > 0 ? F[1 - o][a + 1][m] : 0) +
                    F[o][a + 1 + m][k - 1 - m];
            if (c < best) {
              best = c;
              bt = 2;
              bm = m;
            }
          }
        }
        F[o][a][k] = best;
        Ctype[o][a][k] = bt;
        Cm[o][a][k] = bm;
      }
    }
  }
  st = arr;
  gen(1, n, 0);
  printf("%d\n", (int)ops.size());
  string out;
  out.reserve(ops.size() * 2);
  for (char c : ops) {
    out += c;
    out += '\n';
  }
  fputs(out.c_str(), stdout);
}
