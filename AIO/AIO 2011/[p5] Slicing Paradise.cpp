#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, ti; cin >> N;
    vector<bool> is_edge(N + 2, false);
    is_edge[0] = true;
    is_edge[N + 1] = true;

    vector<int> t(N + 1);

    for(int i = 0; i < N; i++) {
        cin >> ti;
        t[ti] = i + 1;
    }

    int curr_res = 1, max_res = 1;
    for(int i = 1; i <= N; i++) {
        curr_res++;
        if(is_edge[t[i] + 1]) curr_res--;
        if(is_edge[t[i] - 1]) curr_res--;
        is_edge[t[i]] = true;

        max_res = max(max_res, curr_res);
        //cout << curr_res << " ";
    }

    cout << max_res;
}