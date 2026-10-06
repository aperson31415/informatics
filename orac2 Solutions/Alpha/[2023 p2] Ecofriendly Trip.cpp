#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

int N, K;
vector<vector<int>> matrix;
vector<vector<int>> line_psums;
vector<vector<int>> rect_psums;

int m(int x) {
    return x + (K-1)/2;
}

int psum(int r1, int r2, int c1, int c2) {
    // bruh logic sucks so im gonna just do case by case
    if(m(r1) == 0 and m(c1) == 0) {
        return rect_psums[m(r2)][m(c2)] + rect_psums[0][0] - rect_psums[m(r2)][0] - rect_psums[0][m(c2)];
    }
    if(m(r1) == 0) {
        return rect_psums[m(r2)][m(c2)] + rect_psums[0][m(c1) - 1] - rect_psums[m(r2)][m(c1) - 1] - rect_psums[0][m(c2)];
    }
    if(m(c1) == 0) {
        return rect_psums[m(r2)][m(c2)] + rect_psums[m(r1) - 1][0] - rect_psums[m(r2)][0] - rect_psums[m(r1) - 1][m(c2)];
    }
    return rect_psums[m(r2)][m(c2)] + rect_psums[m(r1) - 1][m(c1) - 1] - rect_psums[m(r2)][m(c1) - 1] - rect_psums[m(r1) - 1][m(c2)];
}

int square(int sidelen, int x, int y) {
    return psum(y - (sidelen-1)/2, y + (sidelen-1)/2, x - (sidelen-1)/2, x + (sidelen-1)/2);
}

int right_intersect(int sidelen, int x, int y) {
    // (x, y) is the new position
    return psum(y - (sidelen-1)/2, y + (sidelen-1)/2, x - (sidelen-1)/2, x + (sidelen-1)/2 - 1);
}

int down_intersect(int sidelen, int x, int y) {
    // (x, y) is the new position
    return psum(y - (sidelen-1)/2, y + (sidelen-1)/2 - 1, x - (sidelen-1)/2, x + (sidelen-1)/2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    cin >> N >> K;
    matrix.resize(N + K - 1, vector<int>(N + K - 1));
    line_psums.resize(N + K - 1, vector<int>(N + K - 1, 0));
    rect_psums.resize(N + K - 1, vector<int>(N + K - 1, 0));
    vector<vector<int>> dp;

    for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) cin >> matrix[i + (K-1)/2][j + (K-1)/2];

    // Oh well bashing is fun i hope >= 1 is correct.
    if(K == 1) {
        dp.resize(N, vector<int>(N, INT_MAX));

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(i == 0 and j == 0) {
                    dp[i][j] = matrix[i][j];
                } else if(i == 0) {
                    dp[i][j] = dp[i][j - 1] + matrix[i][j];
                } else if(j == 0) {
                    dp[i][j] = dp[i - 1][j] + matrix[i][j];
                } else {
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + matrix[i][j];
                }
                //cout << "(" << j << "," << i << ") is" << dp[i][j] << endl;
            }
        }

        cout << dp[N - 1][N - 1];
        return 0;
    }

    // Make 2d psums
    
    for(int i = 0; i < N + K - 1; i++) {
        for(int j = 0; j < N + K - 1; j++) {
            if(j == 0) {
                line_psums[i][j] = matrix[i][j];
            } else {
                line_psums[i][j] = line_psums[i][j - 1] + matrix[i][j];
            }
        }
    }

    for(int width = 0; width < N + K - 1; width++) {
        for(int height = 0; height < N + K - 1; height++) {
            if(height == 0) {
                rect_psums[height][width] = line_psums[height][width];
            } else {
                rect_psums[height][width] = rect_psums[height - 1][width] + line_psums[height][width];
            }
        }
    }

    // Run dp
    dp.resize(N, vector<int>(N, INT_MAX));
    for(int row = 0; row < N; row++) {
        for(int col = 0; col < N; col++) {
            if(row == 0 and col == 0) {
                dp[row][col] = square(K, col, row);
            } else if(row == 0) {
                dp[row][col] = dp[row][col - 1] + square(K, col, row) - right_intersect(K, col, row);
            } else if(col == 0) {
                dp[row][col] = dp[row - 1][col] + square(K, col, row) - down_intersect(K, col, row);
            } else {
                dp[row][col] = min(dp[row - 1][col] - down_intersect(K, col, row), dp[row][col - 1] - right_intersect(K, col, row)) + square(K, col, row);
            }
            //cout << "(" << col << "," << row << ") is" << dp[row][col] << endl;
        }
    }

    cout << dp[N - 1][N - 1];
}