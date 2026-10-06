#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int N, H, F; cin >> N >> H >> F;
    vector<int> positions(H + 2);
    for(int i = 1; i <= H; i++) cin >> positions[i];
    positions[0] = 0;
    positions[H + 1] = N + 1;

    priority_queue<int> fence2x;
    vector<int> fence1x;

    for(int i = 0; i <= H; i++) {
        if(i == 0 or i == H) {
            fence1x.push_back(positions[i + 1] - positions[i] - 1);
        } else {
            fence2x.push(positions[i + 1] - positions[i] - 1);
        }
    }

    int res = 0;
    if(F % 2 == 1) {
        // Have to use at least 1x 1-fence
        res += max(fence1x[0], fence1x[1]);
        F--;

        fence2x.push(min(fence1x[0], fence1x[1]));

        for(int i = F / 2; i > 0; i--) {
            if(!fence2x.empty()) {
                res += fence2x.top();
                fence2x.pop();
            }
        }
    } else {
        fence2x.push(fence1x[0] + fence1x[1]);
        for(int i = F / 2; i > 0; i--) {
            if(!fence2x.empty()) {
                res += fence2x.top();
                fence2x.pop();
            }
        }
    }

    cout << res;
}