#include <bits/stdc++.h>
using namespace std;

struct Point {
  long long x, y;
  bool operator<(const Point &o) const {
    if (x != o.x)
      return x < o.x;
    return y < o.y;
  }
  bool operator==(const Point &o) const { return x == o.x && y == o.y; }
};

struct Edge {
  Point p1, p2;
  bool operator<(const Edge &o) const {
    if (!(p1 == o.p1))
      return p1 < o.p1;
    return p2 < o.p2;
  }
  bool operator==(const Edge &o) const { return p1 == o.p1 && p2 == o.p2; }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  vector<Point> pts(n);
  long long xmin = 2e18, xmax = -2e18;
  long long ymin = 2e18, ymax = -2e18;

  for (int i = 0; i < n; ++i) {
    cin >> pts[i].x >> pts[i].y;
    xmin = min(xmin, pts[i].x);
    xmax = max(xmax, pts[i].x);
    ymin = min(ymin, pts[i].y);
    ymax = max(ymax, pts[i].y);
  }

  auto get_edges = [&](const vector<Point> &p_list) {
    vector<Edge> edges(n);
    for (int i = 0; i < n; ++i) {
      Point a = p_list[i];
      Point b = p_list[(i + 1) % n];
      if (!(a < b))
        swap(a, b);
      edges[i] = {a, b};
    }
    sort(edges.begin(), edges.end());
    return edges;
  };

  vector<Edge> orig_edges = get_edges(pts);

  long long CX = xmin + xmax;
  long long CY = ymin + ymax;
  bool is_square = (xmax - xmin == ymax - ymin);

  auto transform = [&](long long X, long long Y, int type) -> Point {
    long long nx = X, ny = Y;
    if (type == 1) {
      nx = 2 * CX - X;
      ny = 2 * CY - Y;
    } else if (type == 2) {
      nx = 2 * CX - X;
      ny = Y;
    } else if (type == 3) {
      nx = X;
      ny = 2 * CY - Y;
    } else if (type == 4) {
      nx = CX + CY - Y;
      ny = X + CY - CX;
    } else if (type == 5) {
      nx = CX + Y - CY;
      ny = CX + CY - X;
    } else if (type == 6) {
      nx = CX + Y - CY;
      ny = CY + X - CX;
    } else if (type == 7) {
      nx = CX - Y + CY;
      ny = CY - X + CX;
    }
    return {nx / 2, ny / 2};
  };

  vector<int> candidate_types = {1, 2, 3};
  if (is_square) {
    candidate_types.push_back(4);
    candidate_types.push_back(5);
    candidate_types.push_back(6);
    candidate_types.push_back(7);
  }

  vector<vector<Point>> valid_transforms;

  for (int type : candidate_types) {
    vector<Point> t_pts(n);
    for (int i = 0; i < n; ++i) {
      t_pts[i] = transform(2 * pts[i].x, 2 * pts[i].y, type);
    }
    vector<Edge> t_edges = get_edges(t_pts);
    if (t_edges == orig_edges) {
      valid_transforms.push_back(t_pts);
    }
  }

  cout << valid_transforms.size() << "\n";
  for (size_t i = 0; i < valid_transforms.size(); ++i) {
    if (i > 0)
      cout << "\n";
    for (int j = 0; j < n; ++j) {
      cout << valid_transforms[i][j].x << " " << valid_transforms[i][j].y
           << "\n";
    }
  }
}
