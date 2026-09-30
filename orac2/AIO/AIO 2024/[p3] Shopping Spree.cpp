#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int N, K;
    cin >> N >> K;
    vector<int> C(N);
    for(int i = 0; i < N; i++) cin >> C[i];
    int discounted = 0;
    for(int i = 0; i < K; i++) {
        discounted += C[i];
    }
    int other = 0;
    for(int i = K + 1; i < N - K; i += 2) {
        other += C[i];
    }
 
    cout << (discounted + other);
}
