#include <bits/stdc++.h>
using namespace std;

signed main() {
    int N; cin >> N;

    vector<long long> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    vector<long long> P(N + 1, 0);
    for (int i = 0; i < N; i++) {
        P[i + 1] = P[i] + A[i];
    }

    vector<long long> S(N + 2, 0);
    for (int i = 0; i <= N; i++) {
        S[i + 1] = S[i] + P[i];
    }

    double total_avg = 0;
    for (int L = 1; L <= N; L++) {
        long long current_len_sum = (S[N + 1] - S[L]) - (S[N - L + 1] - S[0]);
        total_avg += (double) current_len_sum / L;
    }

    long long total_subsegments = (long long) N * (N + 1) / 2;
    double result = total_avg / total_subsegments;

    cout << (long long) result;
}