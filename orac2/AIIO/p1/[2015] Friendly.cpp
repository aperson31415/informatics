#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    int n, k; cin >> n >> k;

    vector<int> max_choc(k + 1, -1);
    vector<vector<int>> starters(k + 1);

    for (int i = 1; i <= k; i++) {
        max_choc[i] = 0;
        starters[i].push_back(i);
    }

    for (int i = 0; i < n; i++) {
        int ai, bi;
        int ci;
        cin >> ai >> bi >> ci;

        if (max_choc[ai] == -1) continue;

        int new_choc = max_choc[ai] + ci;

        if (new_choc > max_choc[bi]) {
            max_choc[bi] = new_choc;
            starters[bi] = starters[ai]; 
        } else if (new_choc == max_choc[bi]) {
            auto& dest = starters[bi];
            const auto& src = starters[ai];
            
            vector<int> merged;
            merged.reserve(dest.size() + src.size());
            merge(dest.begin(), dest.end(), src.begin(), src.end(), back_inserter(merged));
            merged.erase(unique(merged.begin(), merged.end()), merged.end());
            dest = move(merged);
        }
    }

    int global_max_choc = -1;
    vector<int> final_starters;

    for (int i = 1; i <= k; i++) {
        if (max_choc[i] > global_max_choc) {
            global_max_choc = max_choc[i];
            final_starters = starters[i];
        } else if (max_choc[i] == global_max_choc && global_max_choc != -1) {
            auto& dest = final_starters;
            const auto& src = starters[i];
            
            vector<int> merged;
            merged.reserve(dest.size() + src.size());
            merge(dest.begin(), dest.end(), src.begin(), src.end(), back_inserter(merged));
            merged.erase(unique(merged.begin(), merged.end()), merged.end());
            dest = move(merged);
        }
    }

    cout << (global_max_choc == -1 ? 0 : global_max_choc) << '\n' << final_starters.size(); 
}
