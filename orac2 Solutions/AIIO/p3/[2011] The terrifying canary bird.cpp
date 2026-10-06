#include <bits/stdc++.h>
using namespace std;
#define fio(in,out) freopen(in,"r",stdin); freopen(out,"w",stdout)


const int m = 1'000'003;
const vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct square {
  int val, row, col;
  bool operator<(const square& other) const {
    if(val != other.val) return val < other.val;
    if(row != other.row) return row < other.row;
    if(col != other.col) return col < other.col;
    return true;
  }
};

int main() {
  fio("birdin.txt", "birdout.txt");
  int r, c; cin >> r >> c;
  vector<vector<int>> matrix(r + 2, vector<int>(c + 2));
  for(int i = 1; i <= r; i++) {
    for(int j = 1; j <= c; j++) {
      cin >> matrix[i][j];
    }
  }

  vector<square> valsort;
  for(int i = 1; i <= r; i++) {
    for(int j = 1; j <= c; j++) {
      valsort.push_back({matrix[i][j], i, j});
    }
  }

  sort(valsort.begin(), valsort.end());
  reverse(valsort.begin(), valsort.end());

  // dp[i][j] := number of sequences ending at (i, j)
  vector<vector<int>> dp(r + 2, vector<int>(c + 2, 0));
  for(int i = 1; i <= r; i++) {
    for(int j = 1; j <= c; j++) {
      bool base = true;
      for(auto [deltx, delty] : dirs) {
        if(matrix[i + deltx][j + delty] == 0) continue;
        if(matrix[i + deltx][j + delty] > matrix[i][j]) base = false;
      }
      if(base) dp[i][j] = 1;
    }
  }

  for(square thing : valsort) {
    if(dp[thing.row][thing.col] != 0) continue;
    for(auto [deltx, delty] : dirs) {
      dp[thing.row][thing.col] += dp[thing.row + deltx][thing.col + delty]%m;
      dp[thing.row][thing.col] %= m;
    }
  }

  // Get results
  int res = 0;
  for(int i = 1; i <= r; i++) {
    for(int j = 1; j <= c; j++) {
      bool minima = true;
      for(auto [deltx, delty] : dirs) {
        if(matrix[i+deltx][j+delty] == 0) continue;
        if(matrix[i+deltx][j+delty] < matrix[i][j]) minima = false;
      }
      if(minima) res += dp[i][j]%m;
      res %= m;
    }
  }

  cout << res%m;
}
