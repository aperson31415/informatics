#include <bits/stdc++.h>
using namespace std;

struct point {
    int x, y;
    bool operator<(const point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

struct state {
  int a, b;
};

int main() {
  int t; cin >> t;
  vector<point> trolleys(t);
  for(int i = 0; i < t; i++) cin >> trolleys[i].x >> trolleys[i].y;

  vector<vector<int>> trolleybyx(10001);
  for(int i = 0; i < t; i++) trolleybyx[trolleys[i].x].push_back(trolleys[i].y);

  vector<int> coltype(10001, 0);
  vector<int> goodcols;
  vector<pair<int, int>> minmaxcol(10001);
  for(int i = 0; i <= 10000; i++) {
    if(trolleybyx[i].size() == 0) continue;
    else if(trolleybyx[i].size() == 1) {
      coltype[i] = 1;
      minmaxcol[i] = {trolleybyx[i][0], trolleybyx[i][0]};
      goodcols.push_back(i);
    } else {
      coltype[i] = 2;
      minmaxcol[i] = {*min_element(trolleybyx[i].begin(), trolleybyx[i].end()), *max_element(trolleybyx[i].begin(), trolleybyx[i].end())};
      goodcols.push_back(i);
    }
  }

  // dp
  map<point, state> dp;
  dp[{minmaxcol[goodcols[0]].first, goodcols[0]}] = {0, minmaxcol[goodcols[0]].second - minmaxcol[goodcols[0]].first};
  dp[{minmaxcol[goodcols[0]].second, goodcols[0]}] = {0, minmaxcol[goodcols[0]].second - minmaxcol[goodcols[0]].first};
  
  for(int i = 1; i < (int) goodcols.size(); i++) {
    int x_prev = goodcols[i-1];
    int x_curr = goodcols[i];
    int dx = x_curr - x_prev;

    int y_prev_min = minmaxcol[x_prev].first;
    int y_prev_max = minmaxcol[x_prev].second;
    int y_curr_min = minmaxcol[x_curr].first;
    int y_curr_max = minmaxcol[x_curr].second;

    // Init
    dp[{y_curr_min, x_curr}] = {-1, -1};
    dp[{y_curr_max, x_curr}] = {-1, -1};
    
    // a: arriving at min or max of current column with vertical + horizontal distance
    dp[{y_curr_min, x_curr}].a = min(
        dx + abs(y_prev_min - y_curr_min) + dp[{y_prev_min, x_prev}].b,
        dx + abs(y_prev_max - y_curr_min) + dp[{y_prev_max, x_prev}].b
      );
    dp[{y_curr_max, x_curr}].a = min(
        dx + abs(y_prev_min - y_curr_max) + dp[{y_prev_min, x_prev}].b,
        dx + abs(y_prev_max - y_curr_max) + dp[{y_prev_max, x_prev}].b
      );
      
    // b: fully covering current column
    int range = y_curr_max - y_curr_min;
    dp[{y_curr_min, x_curr}].b = dp[{y_curr_max, x_curr}].a + range;
    dp[{y_curr_max, x_curr}].b = dp[{y_curr_min, x_curr}].a + range;
  }

  // get results
  int last_col = goodcols.back();
  int res = min(
      dp[{minmaxcol[last_col].first, last_col}].b,
      dp[{minmaxcol[last_col].second, last_col}].b
      );

  cout << res;
}
