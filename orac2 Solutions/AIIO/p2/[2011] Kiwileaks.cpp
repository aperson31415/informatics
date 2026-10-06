#include <bits/stdc++.h>
using namespace std;

#define int long long

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int gcd(int a, int b) {
    if(a == 0) {
        return b;
    } else if(b == 0) {
        return a;
    }
    return gcd(min(a, b), max(a, b) % min(a, b));
}

signed main() {
    freopen("leakin.txt", "r", stdin);
    freopen("leakout.txt", "w", stdout);

    int N, K; cin >> N >> K;
    vector<int> cipher(N + 1), a(K);
    for(int i = 1; i <= N; i++) cin >> cipher[i];
    for(int i = 0; i < K; i++) cin >> a[i];

    // For each, see if there is a loop (should be < 205 'operations')
    vector<int> cycle_length(K, -1);
    for(int i = 0; i < K; i++) {
        int curr = a[i];
        for(int j = 1; j < N + 10; j++) {
            curr = cipher[curr];
            if(curr == a[i]) {
                cycle_length[i] = j;
                break;
            }
        }
    }

    // Check if impossible
    for(int i = 0; i < K; i++) {
        if(cycle_length[i] == -1) {
            cout << "Impossible";
            return 0;
        }
    }

    // Find lcm
    int curr_lcm = cycle_length[0];
    for(int i = 1; i < K; i++) {
        curr_lcm = lcm(curr_lcm, cycle_length[i]);
        //cout << "at idx " << i << ", lcm is " << curr_lcm << '\n';
    }
    cout << curr_lcm;
}