#include <bits/stdc++.h>
using namespace std;

int main() {
  int R, C;
  cin >> R >> C;

  vector<string> grid(R);
  vector<vector<int>> S(R, vector<int>(C, 0));
  for (int r = 0; r < R; ++r) {
    cin >> grid[r];
    for (int c = 0; c < C; ++c) {
      if (grid[r][c] == '.') {
        S[r][c] = 1; // Needs to be toggled on
      } else {
        S[r][c] = 0; // Already on
      }
    }
  }

  int N = R + C;
  // Variables 0 to R-1 represent R_r
  // Variables R to R+C-1 represent C_c
  vector<vector<int>> mat(N, vector<int>(N + 1, 0));

  int coeff_R = (C + 1) % 2;
  for (int r = 0; r < R; ++r) {
    if (coeff_R == 1) {
      mat[r][r] = 1;
    }
    for (int c = 0; c < C; ++c) {
      mat[r][R + c] = 1;
    }
    int sum_S = 0;
    for (int c = 0; c < C; ++c) {
      sum_S ^= S[r][c];
    }
    mat[r][N] = sum_S;
  }

  int coeff_C = (R + 1) % 2;
  for (int c = 0; c < C; ++c) {
    for (int r = 0; r < R; ++r) {
      mat[R + c][r] = 1;
    }
    if (coeff_C == 1) {
      mat[R + c][R + c] = 1;
    }
    int sum_S = 0;
    for (int r = 0; r < R; ++r) {
      sum_S ^= S[r][c];
    }
    mat[R + c][N] = sum_S;
  }

  int row = 0;
  vector<int> lead(N, -1);
  for (int col = 0; col < N && row < N; ++col) {
    int sel = row;
    while (sel < N && mat[sel][col] == 0) {
      sel++;
    }
    if (sel == N)
      continue;

    swap(mat[sel], mat[row]);
    lead[row] = col;

    for (int i = 0; i < N; ++i) {
      if (i != row && mat[i][col] == 1) {
        for (int j = col; j <= N; ++j) {
          mat[i][j] ^= mat[row][j];
        }
      }
    }
    row++;
  }

  for (int i = row; i < N; ++i) {
    if (mat[i][N] != 0) {
      cout << -1 << "\n";
      return 0;
    }
  }

  vector<int> ans_vars(N, 0);
  for (int i = 0; i < row; ++i) {
    int c = lead[i];
    if (c != -1) {
      ans_vars[c] = mat[i][N];
    }
  }

  vector<int> R_val(R);
  vector<int> C_val(C);
  for (int r = 0; r < R; ++r)
    R_val[r] = ans_vars[r];
  for (int c = 0; c < C; ++c)
    C_val[c] = ans_vars[R + c];

  vector<pair<int, int>> flips;
  for (int r = 0; r < R; ++r) {
    for (int c = 0; c < C; ++c) {
      int x = S[r][c] ^ R_val[r] ^ C_val[c];
      if (x == 1) {
        flips.push_back({r, c});
      }
    }
  }

  cout << flips.size() << "\n";
  for (auto &p : flips) {
    cout << p.first << " " << p.second << "\n";
  }
}
