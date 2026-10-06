#include <bits/stdc++.h>
using namespace std;

struct State {
    int x, y, z;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c, d;
    cin >> a >> b >> c;
    cin >> d;

    int cap[3] = {a, b, c};

    // Encode (x, y, z) as one integer.
    // Since x + y + z = a, y and z uniquely identify the state.
    int W = c + 1;

    auto encode = [&](int x, int y, int z) {
        return y * W + z;
    };

    int maxStates = (b + 1) * (c + 1);

    vector<char> visited(maxStates, false);
    vector<int> parent(maxStates, -1);
    vector<int> moveFrom(maxStates, -1);
    vector<int> moveTo(maxStates, -1);

    queue<State> q;

    State start = {a, 0, 0};
    int startID = encode(start.x, start.y, start.z);

    visited[startID] = true;
    q.push(start);

    State answer;
    bool found = false;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        // Have we measured d ounces?
        if (cur.x == d || cur.y == d || cur.z == d) {
            answer = cur;
            found = true;
            break;
        }

        int amount[3] = {cur.x, cur.y, cur.z};

        // Try all 6 possible pours.
        for (int from = 0; from < 3; from++) {
            for (int to = 0; to < 3; to++) {
                if (from == to)
                    continue;

                // Nothing to pour, or destination already full.
                if (amount[from] == 0 || amount[to] == cap[to])
                    continue;

                State nxt = cur;

                int poured = min(amount[from],
                                 cap[to] - amount[to]);

                if (from == 0) nxt.x -= poured;
                if (from == 1) nxt.y -= poured;
                if (from == 2) nxt.z -= poured;

                if (to == 0) nxt.x += poured;
                if (to == 1) nxt.y += poured;
                if (to == 2) nxt.z += poured;

                int id = encode(nxt.x, nxt.y, nxt.z);

                if (visited[id])
                    continue;

                visited[id] = true;
                parent[id] = encode(cur.x, cur.y, cur.z);
                moveFrom[id] = from + 1;
                moveTo[id] = to + 1;

                q.push(nxt);
            }
        }
    }

    // No solution.
    if (!found) {
        cout << "0 0\n";
        return 0;
    }

    // Reconstruct the path backwards.
    vector<pair<int, int>> answerMoves;

    int curID = encode(answer.x, answer.y, answer.z);

    while (curID != startID) {
        answerMoves.push_back({
            moveFrom[curID],
            moveTo[curID]
        });

        curID = parent[curID];
    }

    // We reconstructed backwards, so reverse it.
    reverse(answerMoves.begin(), answerMoves.end());

    for (auto [from, to] : answerMoves) {
        cout << from << ' ' << to << '\n';
    }

    // Print the jug containing d.
    if (answer.x == d)
        cout << "0 1\n";
    else if (answer.y == d)
        cout << "0 2\n";
    else
        cout << "0 3\n";

    return 0;
}

