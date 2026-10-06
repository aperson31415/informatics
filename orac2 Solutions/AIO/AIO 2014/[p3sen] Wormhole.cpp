#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R, C, Q;
    cin >> R >> C >> Q;

    vector<string> grid(R);
    for (auto &row : grid)
        cin >> row;

    // cntRow[r][0] = number of O in row r
    // cntRow[r][1] = number of B in row r
    //
    // cntCol[c][0] = number of O in column c
    // cntCol[c][1] = number of B in column c
    vector<array<int, 2>> cntRow(R);
    vector<array<int, 2>> cntCol(C);

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            int colour = (grid[r][c] == 'B');

            cntRow[r][colour]++;
            cntCol[c][colour]++;
        }
    }

    auto answer = [&]() -> int {

        // 1 x 1
        if (R == 1 && C == 1)
            return 0;

        // 1 x N or N x 1
        if (R == 1 || C == 1) {
            if (R == 1) {
                bool allO = (cntRow[0][0] == C);
                bool allB = (cntRow[0][1] == C);

                return (allO || allB) ? 1 : 0;
            } else {
                bool allO = (cntCol[0][0] == R);
                bool allB = (cntCol[0][1] == R);

                return (allO || allB) ? 1 : 0;
            }
        }

        // R,C >= 2

        int fullRowsO = 0;
        int fullRowsB = 0;
        int fullColsO = 0;
        int fullColsB = 0;

        // Completely orange / blue rows
        for (int r = 0; r < R; r++) {
            if (cntRow[r][0] == C)
                fullRowsO++;

            if (cntRow[r][1] == C)
                fullRowsB++;
        }

        // Completely orange / blue columns
        for (int c = 0; c < C; c++) {
            if (cntCol[c][0] == R)
                fullColsO++;

            if (cntCol[c][1] == R)
                fullColsB++;
        }

        // Entire grid is one colour.
        //
        // Need min(R, C) changes.
        bool allO = (fullRowsO == R);
        bool allB = (fullRowsB == R);

        if (allO || allB)
            return min(R, C);

        // Special case:
        //
        // If R == 2 and both rows are monochromatic with
        // different colours, the answer is 2.
        //
        // Likewise for C == 2 and both columns are
        // monochromatic with different colours.
        bool twoDifferentRows =
            R == 2 &&
            fullRowsO == 1 &&
            fullRowsB == 1;

        bool twoDifferentCols =
            C == 2 &&
            fullColsO == 1 &&
            fullColsB == 1;

        if (twoDifferentRows || twoDifferentCols)
            return 2;

        // If every row is monochromatic, or every column is
        // monochromatic, the wormhole graph is disconnected.
        // One colour change is enough to fix it.
        bool allRowsMonochromatic =
            fullRowsO + fullRowsB == R;

        bool allColsMonochromatic =
            fullColsO + fullColsB == C;

        if (allRowsMonochromatic || allColsMonochromatic)
            return 1;

        return min(fullRowsO, fullColsO)
             + min(fullRowsB, fullColsB);
    };

    // Initial answer
    cout << answer() << '\n';

    // Updates
    while (Q--) {
        int r, c;
        cin >> r >> c;

        --r;
        --c;

        int oldColour = (grid[r][c] == 'B');
        int newColour = 1 - oldColour;

        // Update row counts
        cntRow[r][oldColour]--;
        cntRow[r][newColour]++;

        // Update column counts
        cntCol[c][oldColour]--;
        cntCol[c][newColour]++;

        // Update grid
        grid[r][c] = (newColour == 0 ? 'O' : 'B');

        cout << answer() << '\n';
    }
}

