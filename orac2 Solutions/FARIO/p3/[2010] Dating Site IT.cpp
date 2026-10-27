#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100;
int diff[MAXN][MAXN][MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int S, U;
  cin >> S >> U;

  for (int i = 0; i < S; ++i) {
    int x1, x2, y1, y2, z1, z2;
    cin >> x1 >> x2 >> y1 >> y2 >> z1 >> z2;

    // 0 upper bounds (+val)
    diff[x1][y1][z1] += 1;

    // 1 upper bound (-val)
    if (x2 + 1 < MAXN)
      diff[x2 + 1][y1][z1] -= 1;
    if (y2 + 1 < MAXN)
      diff[x1][y2 + 1][z1] -= 1;
    if (z2 + 1 < MAXN)
      diff[x1][y1][z2 + 1] -= 1;

    // 2 upper bounds (+val)
    if (x2 + 1 < MAXN && y2 + 1 < MAXN)
      diff[x2 + 1][y2 + 1][z1] += 1;
    if (x2 + 1 < MAXN && z2 + 1 < MAXN)
      diff[x2 + 1][y1][z2 + 1] += 1;
    if (y2 + 1 < MAXN && z2 + 1 < MAXN)
      diff[x1][y2 + 1][z2 + 1] += 1;

    // 3 upper bounds (-val)
    if (x2 + 1 < MAXN && y2 + 1 < MAXN && z2 + 1 < MAXN) {
      diff[x2 + 1][y2 + 1][z2 + 1] -= 1;
    }
  }

  // Along X-axis
  for (int y = 0; y < MAXN; ++y) {
    for (int z = 0; z < MAXN; ++z) {
      for (int x = 1; x < MAXN; ++x) {
        diff[x][y][z] += diff[x - 1][y][z];
      }
    }
  }

  // Along Y-axis
  for (int x = 0; x < MAXN; ++x) {
    for (int z = 0; z < MAXN; ++z) {
      for (int y = 1; y < MAXN; ++y) {
        diff[x][y][z] += diff[x][y - 1][z];
      }
    }
  }

  // Along Z-axis
  for (int x = 0; x < MAXN; ++x) {
    for (int y = 0; y < MAXN; ++y) {
      for (int z = 1; z < MAXN; ++z) {
        diff[x][y][z] += diff[x][y][z - 1];
      }
    }
  }

  long long total_legitimate_visits = 0;
  for (int i = 0; i < U; ++i) {
    int a, h, w, v;
    cin >> a >> h >> w >> v;

    if (diff[a][h][w] == 0) {
      total_legitimate_visits += v;
    }
  }

  cout << total_legitimate_visits;
}
