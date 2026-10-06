#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int r, c;
    cin >> r >> c;
    
    vector<vector<int>> matrix(r, vector<int>(c, 0));
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            char x; cin >> x;
            if(x == '.') matrix[i][j] = 1;
        }
    }
 
    int res = 0;
    int curr = 0;
    int r1, c1, r2, c2, left = -1;
 
    for(int i = 0; i < r; i++) {
        curr = 0;
        left = 0;
        for(int j = 0; j < c; j++) {
            if(matrix[i][j]) curr++;
            else curr = 0;
 
            if(curr == 1) left = j;
 
            if(curr > res) {
                res = curr;
                r1 = i; r2 = i;
                c1 = left; c2 = j;
            }
        }
    }
 
    for(int j = 0; j < c; j++) {
        curr = 0;
        left = 0;
        for(int i = 0; i < r; i++) {
            if(matrix[i][j]) curr++;
            else {curr = 0;}
 
            if(curr == 1) left = i;
 
            if(curr > res) {
                res = curr;
                c1 = j; c2 = j;
                r1 = left; r2 = i;
            }
        }
    }
 
    cout << r1 + 1 << " " << c1 + 1 << " " << r2 + 1 << " " << c2 + 1;
}
