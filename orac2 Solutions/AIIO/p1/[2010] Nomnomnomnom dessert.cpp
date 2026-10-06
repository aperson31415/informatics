#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

#define int long long

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    #ifndef local
        freopen("nomin.txt","r",stdin); freopen("nomout.txt", "w",stdout);
    #endif

    int N; cin >> N;
    vector<int> s(N);
    for(int i = 0; i < N; i++) cin >> s[i];
    vector<int> psums(N + 1, 0);
    for(int i = 1; i <= N; i++) psums[i] = psums[i - 1] + s[i - 1];

    int res = 0;
    for(int B = 0; B <= N; B++) {
        auto find = lower_bound(psums.begin(), psums.end(), 2*psums[B]);
        if(find == psums.end()) continue;
        if(*find == 2*psums[B]) {
            res = max(res, psums[B]);
        }
    }

    cout << res;
}