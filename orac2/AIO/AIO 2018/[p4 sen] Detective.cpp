#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int type; // +1 = same, -1 = different
};

struct Component {
    int plusCnt = 0;      // number of Xt nodes coloured +1
    int minusCnt = 0;     // number of Xt nodes coloured -1

    int plusThief = -1;   // child whose Xt node is +1, if unique
    int minusThief = -1;  // child whose Xt node is -1, if unique
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M; cin >> N >> M; 
    int V = 2 * N;

    vector<vector<Edge>> graph(V + 1);

    auto addEdge = [&](int u, int v, int relation) {
        graph[u].push_back({v, relation});
        graph[v].push_back({u, relation});
    };

    for (int i = 0; i < M; i++) {
        int A, B, type;
        cin >> A >> B >> type;

        if (type == 1) addEdge(A, B, +1);
        else if (type == 2) addEdge(A, B, -1);
        else addEdge(A, N + B, +1);
    }

    vector<int> colour(V + 1, 0);
    vector<Component> components;

    bool inconsistent = false;

    for (int start = 1; start <= V; start++) {
        if (colour[start] != 0) continue;

        Component comp;
        queue<int> q;

        // Arbitrarily choose this node to be true.
        colour[start] = +1;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u > N) {
                int child = u - N;

                if (colour[u] == +1) {
                    comp.plusCnt++;
                    comp.plusThief = child;
                }
                else {
                    comp.minusCnt++;
                    comp.minusThief = child;
                }
            }

            for (Edge e : graph[u]) {
                int v = e.to;

                int requiredColour = colour[u] * e.type;

                if (colour[v] == 0) {
                    colour[v] = requiredColour;
                    q.push(v);
                }
                else if (colour[v] != requiredColour) {
                    inconsistent = true;
                }
            }
        }

        components.push_back(comp);
    }

    if (inconsistent) {
        cout << "MISTAKE\n";
        return 0;
    }

    int forcedComponents = 0;
    int forcedComponent = -1;

    for (int i = 0; i < (int)components.size(); i++) {
        Component &c = components[i];

        if (c.plusCnt > 0 && c.minusCnt > 0) {
            forcedComponents++;
            forcedComponent = i;
        }
    }

    if (forcedComponents > 1) {
        cout << "MISTAKE\n";
        return 0;
    }

    vector<int> answer;

    for (int i = 0; i < (int)components.size(); i++) {
        Component &c = components[i];

        if (forcedComponents == 1 && i != forcedComponent) continue;

        if (c.plusCnt == 1) answer.push_back(c.plusThief);
        if (c.minusCnt == 1) answer.push_back(c.minusThief);
    }

    sort(answer.begin(), answer.end());
    answer.erase(unique(answer.begin(), answer.end()), answer.end());

    if (answer.empty()) cout << "MISTAKE\n";
    else for (int child : answer) cout << child << '\n';
}

