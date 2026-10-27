#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
  int H, W;
  cin >> H >> W;

  vector<vector<long long>> A(H, vector<long long>(W));
  for (int r = 0; r < H; ++r) {
    for (int c = 0; c < W; ++c) {
      cin >> A[r][c];
    }
  }

  // pref[r][c] = sum of column c from row 0 down to row r
  vector<vector<long long>> pref(H, vector<long long>(W, 0));
  for (int c = 0; c < W; ++c) {
    pref[0][c] = A[0][c];
    for (int r = 1; r < H; ++r) {
      pref[r][c] = pref[r - 1][c] + A[r][c];
    }
  }

  auto get_cost = [&](int c, int h) {
    if (h == 0)
      return 0LL;
    // Bottom h blocks span from row (H - h) to (H - 1)
    long long total = pref[H - 1][c];
    if (H - h - 1 >= 0) {
      total -= pref[H - h - 1][c];
    }
    return total;
  };

  // left_dp[i][h]: max score for columns 1 to i (1-indexed), where column i has
  // height h (non-decreasing left-to-right)
  vector<vector<long long>> left_dp(W + 2, vector<long long>(H + 1, -INF));
  // right_dp[i][h]: max score for columns W down to i, where column i has
  // height h (non-decreasing right-to-left)
  vector<vector<long long>> right_dp(W + 2, vector<long long>(H + 1, -INF));

  // Base cases for boundaries outside the board
  left_dp[0][0] = 0;
  right_dp[W + 1][0] = 0;

  // Fill left_dp from left to right (i = 1 to W)
  for (int i = 1; i <= W; ++i) {
    long long max_prev = -INF;
    for (int h = 0; h <= H; ++h) {
      max_prev = max(max_prev, left_dp[i - 1][h]);
      if (max_prev != -INF) {
        left_dp[i][h] = max_prev + get_cost(i - 1, h);
      }
    }
  }

  // Fill right_dp from right to left (i = W down to 1)
  for (int i = W; i >= 1; --i) {
    long long max_prev = -INF;
    for (int h = 0; h <= H; ++h) {
      max_prev = max(max_prev, right_dp[i + 1][h]);
      if (max_prev != -INF) {
        right_dp[i][h] = max_prev + get_cost(i - 1, h);
      }
    }
  }

  // Combine both halves at each possible peak column 'i' and height 'h'
  long long max_score = -INF;
  for (int i = 1; i <= W; ++i) {
    for (int h = 0; h <= H; ++h) {
      if (left_dp[i][h] != -INF && right_dp[i][h] != -INF) {
        long long current = left_dp[i][h] + right_dp[i][h] - get_cost(i - 1, h);
        max_score = max(max_score, current);
      }
    }
  }

  cout << max_score;
}
