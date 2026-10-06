#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("servin.txt", "r", stdin); freopen("servout.txt", "w", stdout);
    int r, c; cin >> r >> c;

    int row = 1;
    int col = 1;

    // true  = monogram faces the top
    // false = monogram faces the bottom
    bool faceTop = true;
    bool visible = true;

    char dir;
    int line;

    while (cin >> dir >> line) {
        if (!visible) continue;

        if (dir == 'V' || dir == 'v') {
            int k = line;
            bool folded = (col <= k);

            if (folded) {
                faceTop = !faceTop;
                col = k + 1 - col;
            } else {
                bool coveredSideIsTop = (dir == 'V');
                if (faceTop == coveredSideIsTop) visible = false;
                col = col - k;
            }

            c = max(k, c - k);
        }
        else {
            int k = line;
            bool folded = (row <= k);

            if (folded) {
                faceTop = !faceTop;
                row = k + 1 - row;
            } else {
                bool coveredSideIsTop = (dir == 'H');
                if (faceTop == coveredSideIsTop) visible = false;
                row = row - k;
            }

            r = max(k, r - k);
        }
    }

    cout << (visible ? "visible" : "not visible");
}

