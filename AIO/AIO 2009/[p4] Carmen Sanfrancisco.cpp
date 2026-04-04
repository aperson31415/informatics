#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

struct node {
    int neighbour, transport;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<vector<node>> adj(N);
    for(int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a-1].push_back({b-1, c});
        adj[b-1].push_back({a-1, c});
    }

    int K;
    cin >> K;
    vector<int> transports(K);
    for(int i = 0; i < K; i++) cin >> transports[i];

    vector<bool> possible(N, true); 

    for (int k = 0; k < K; k++) {
        vector<bool> next_possible(N, false);
        int current_transport = transports[k];

        for (int u = 0; u < N; u++) {
            if (possible[u]) {
                for (auto& edge : adj[u]) {
                    if (edge.transport == current_transport) {
                        next_possible[edge.neighbour] = true;
                    }
                }
            }
        }
        
        possible = move(next_possible);
    }

    bool found = false;
    for (int i = 0; i < N; i++) {
        if (possible[i]) {
            cout << i + 1 << "\n";
            found = true;
        }
    }

    if (!found) cout << "Impossible" << endl;

    return 0;
}