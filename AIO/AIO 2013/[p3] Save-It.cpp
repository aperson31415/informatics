#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    long long total_cost = 0;
    long long cnt[5] = {0, 0, 0, 0, 0};

    for (int i = 0; i < N; i++) {
        long long c;
        cin >> c;
        total_cost += (c / 5) * 5;
        cnt[c % 5]++;
    }

    long long penalty_cost = (cnt[3] + cnt[4]) * 5;
    long long savings = 0;

    long long s1 = min(cnt[3], cnt[4]);
    savings += s1 * 5;
    cnt[3] -= s1;
    cnt[4] -= s1;

    long long s2 = cnt[3] / 2;
    savings += s2 * 5;
    cnt[3] %= 2;

    long long s3 = cnt[4] / 3;
    savings += s3 * 5;
    cnt[4] %= 3;

    cout << total_cost + penalty_cost - savings << endl;

    return 0;
}