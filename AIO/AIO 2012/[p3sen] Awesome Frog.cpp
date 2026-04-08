#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    ll K;
    cin >> N >> K;

    // A[i] := pos[i] - (i * K)
    vector<ll> A(N);
    A[0] = 0;
    
    ll current_pos = 0;
    for (int i = 1; i < N; i++) {
        ll dist;
        cin >> dist;
        current_pos += dist;
        A[i] = current_pos - (i * K);
    }

    // Minimise |A[i] - x|
    sort(A.begin(), A.end());
    
    ll median = A[N / 2];
    
    ll res = 0;
    for (int i = 0; i < N; i++) {
        res += abs(A[i] - median);
    }

    cout << res;
}