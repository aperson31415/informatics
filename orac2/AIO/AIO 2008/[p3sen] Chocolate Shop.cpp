// Why havent more people solved this ?!?!

#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, x; cin >> N;
    int ans = 0;
    for(int i = 0; i < N; i++) {
        cin >> x;
        ans += x;
        ans %= 10;
    }

    cout << (10 - (ans % 10))%10;
}