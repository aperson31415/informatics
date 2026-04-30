#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

#define int long long

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    int X, W; cin >> X >> W;
    vector<int> A(X), warps(W), gain(W, -1);
    for(int i = 0; i < X; i++) cin >> A[i];
    for(int i = 0; i < W; i++) cin >> warps[i];

    int curr = -1;
    for(int i = 0; i < W; i++) {
        // Run sliding window for this warp, total O(XW)
        if(warps[i] > X or warps[i] <= 0) continue;
        int max_gain = -1;
        for(int start = 0; start <= X - warps[i]; start++) {
            if(start == 0) {
                curr = 0;
                for(int j = 0; j < warps[i]; j++) {
                    curr += A[j];
                }
            } else {
                curr -= A[start - 1];
                curr += A[start + warps[i] - 1];
            }
            //cout << "start " << start << ", size " << warps[i] << "val " << curr << "\n";
            max_gain = max(max_gain, curr);
        }
        gain[i] = max_gain;
    }

    // Final stuff
    int res = 0;
    for(auto& elem : A) {
        res += elem;
    }
    for(auto& warp : gain) {
        if(warp > 0) {
            res += warp;
        }
    }

    cout << res;
}