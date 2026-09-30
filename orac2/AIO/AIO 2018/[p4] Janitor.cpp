#include <bits/stdc++.h>
using namespace std;
 
struct point {
    int x, y, val;
    int operator<(point other) const {
        return val > other.val;
    }
};
 
vector<vector<int>> matrix;
const vector<pair<int, int>> adj = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int R, C, Q;
 
bool has_adjbig(int x, int y) {
    for(auto& [deltax, deltay] : adj) {
        if (y + deltay + 1 >= 0 and y + deltay + 1 <= R + 1 and
            x + deltax + 1 >= 0 and x + deltax + 1 <= C + 1) {
                if (matrix[y + deltay + 1][x + deltax + 1] >= matrix[y + 1][x + 1]) {
                    return true;
                }
            } else {
                continue;
            }
    }
    return false;
}
 
int main() {
    cin >> R >> C >> Q;
    matrix.resize(R + 2, vector<int>(C + 2, -1));
    vector<point> stuff;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> matrix[i + 1][j + 1];
            stuff.push_back({j, i, matrix[i + 1][j + 1]});
        }
    }
 
    sort(stuff.begin(), stuff.end());
 
    // Do original stuffs
    int peaks = 0;
    for(point pt : stuff) {
        if (!has_adjbig(pt.x, pt.y)) {
            peaks++;
        }
    }
 
    cout << peaks << "\n";
 
    int r, c, h;
 
    // Do queries
    for(int i = 0; i < Q; i++) {
        cin >> r >> c >> h;
 
        bool adjbig_original = has_adjbig(c - 1, r - 1);
        bool upbig_original = has_adjbig(c - 1, r - 1 + 1);
        bool downbig_original = has_adjbig(c - 1, r - 1 - 1);
        bool leftbig_original = has_adjbig(c - 1 - 1, r - 1);
        bool rightbig_original = has_adjbig(c - 1 + 1, r - 1);
        matrix[r][c] = h;
 
        bool adjbig_updated = has_adjbig(c - 1, r - 1);
        bool upbig_updated = has_adjbig(c - 1, r - 1 + 1);
        bool downbig_updated = has_adjbig(c - 1, r - 1 - 1);
        bool leftbig_updated = has_adjbig(c - 1 - 1, r - 1);
        bool rightbig_updated = has_adjbig(c - 1 + 1, r - 1);
 
        if(adjbig_original and !adjbig_updated) {
            peaks++;
        } else if(!adjbig_original and adjbig_updated) {
            peaks--;
        }
 
        if(upbig_original and !upbig_updated) {peaks++;}
        if(downbig_original and !downbig_updated) {peaks++;}
        if(leftbig_original and !leftbig_updated) {peaks++;}
        if(rightbig_original and !rightbig_updated) {peaks++;}
 
        if(!upbig_original and upbig_updated) {peaks--;}
        if(!downbig_original and downbig_updated) {peaks--;}
        if(!leftbig_original and leftbig_updated) {peaks--;}
        if(!rightbig_original and rightbig_updated) {peaks--;}
 
        cout << peaks << "\n";
    }
}
