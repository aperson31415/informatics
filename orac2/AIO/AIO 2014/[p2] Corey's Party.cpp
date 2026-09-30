#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

struct thingy {
    int friends, id;
    bool operator<(const thingy& other) const {
        if(friends != other.friends) return friends < other.friends;
        return id < other.id;
    }
};

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M, A, B; 
    cin >> N >> M >> A >> B;

    vector<vector<int>> adj(N);
    vector<int> current_deg(N, 0);
    for(int i = 0; i < M; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
        current_deg[x]++;
        current_deg[y]++;
    }

    set<thingy> friends_sorted;
    vector<bool> in_party(N, true);
    for(int i = 0; i < N; i++) {
        friends_sorted.insert({current_deg[i], i});
    }

    int K = N; // Res

    while (!friends_sorted.empty()) {
        bool changed = false;

        // Know not enough
        if (!friends_sorted.empty() && friends_sorted.begin()->friends < A) {
            changed = true;
            int curr_id = friends_sorted.begin()->id;
            friends_sorted.erase(friends_sorted.begin());
            in_party[curr_id] = false;
            K--;

            for (int nb : adj[curr_id]) {
                if (in_party[nb]) {
                    friends_sorted.erase({current_deg[nb], nb});
                    current_deg[nb]--;
                    friends_sorted.insert({current_deg[nb], nb});
                }
            }
        }

        // Know too many
        if (!friends_sorted.empty() && prev(friends_sorted.end())->friends > (K - 1) - B) {
            changed = true;
            int curr_id = prev(friends_sorted.end())->id;
            friends_sorted.erase(prev(friends_sorted.end()));
            in_party[curr_id] = false;
            K--;

            for (int nb : adj[curr_id]) {
                if (in_party[nb]) {
                    friends_sorted.erase({current_deg[nb], nb});
                    current_deg[nb]--;
                    friends_sorted.insert({current_deg[nb], nb});
                }
            }
        }

        if (!changed) break;
    }

    cout << friends_sorted.size();
}