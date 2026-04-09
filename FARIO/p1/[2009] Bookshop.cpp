#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt,sse4,fma")
using namespace std;

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N; cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; i++) cin >> A[i];
    int K; cin >> K;
    vector<int> B(K);
    for(int i = 0; i < K; i++) cin >> B[i];

    int book = 0;
    vector<int> positions(K, -1);

    for(int i = 0; i < N; i++) {
        if(A[i] == B[book]) {
            positions[book] = i + 1;
            book++;
            if(book == K) {
                break;
            }
        }
    }

    for(int i = 0; i < K; i++) {
        cout << positions[i] << '\n';
    }
}