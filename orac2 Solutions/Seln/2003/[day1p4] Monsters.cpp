#include <bits/stdc++.h>
using namespace std;
 
struct amount {
    int val; vector<int> steps;
    bool operator<(const amount& other) const {
        return val < other.val;
    }
};
 
int main() {
    freopen("monsterin.txt", "r", stdin);
    freopen("monsterout.txt", "w", stdout);
 
    int n, s; cin >> n >> s;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    
    vector<vector<set<amount>>> dp(n, vector<set<amount>>(n)); // dp[l][r] = possible scariness from merging l to r
    for(int i = 0; i < n; i++) {
        dp[i][i] = {{a[i], {}}};
    }
    for(int size = 1; size < n; size++) {
        for(int start = 0; start < n - size; start++) {
            int end = start + size;
            for(int split = start; split < end; split++) {
                // Combine dp[start + split][start + size] with dp[start][start + split - 1]
                for(auto& [elem1, steps1] : dp[split + 1][start + size]) {
                    for(auto& [elem2, steps2] : dp[start][split]) {
                        vector<int> combined;
                        combined.insert(combined.end(), steps1.begin(), steps1.end());
                        combined.insert(combined.end(), steps2.begin(), steps2.end());
                        combined.push_back(start);
                        dp[start][start + size].insert({abs(elem1 - elem2), combined});
                    }
                }
            }
        }
    }
    
    for(auto& [value, steps] : dp[0][n-1]) {
        if(value == s) {
            for(auto& elem : steps) cout << elem + 1 << "\n";
            return 0;
        }
    }
    cout << 0;
}