// Way easier than expected!

#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int currseg;

    const int MOD = 1e9 + 7;
    int N; cin >> N;
    vector<int> sum = {0, 0};

    for(int i = 0; i < N; i++) {
        cin >> currseg;
        if(i == 0) {
            sum[currseg] = 1;
            continue;
        }
        if(i == N - 1) {
            cout << sum[(currseg + 1)%2];
            return 0;
        }
        sum[currseg] += sum[(currseg + 1)%2] % MOD;
        sum[currseg] %= MOD;
    }
}