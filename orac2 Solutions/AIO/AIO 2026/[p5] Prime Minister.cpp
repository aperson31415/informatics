#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int N;
    long long K;
    cin >> N >> K;
 
    vector<long long> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
 
    int M = N / 2; // Median index
 
    // Precompute prefix sums for O(1) range sum queries
    vector<long long> pref(N + 1, 0);
    for (int i = 0; i < N; ++i) {
        pref[i + 1] = pref[i] + A[i];
    }
 
    // Binary search range for the maximum possible median
    long long low = A[M];
    long long high = A[M] + K;
    long long ans = low;
 
    while (low <= high) {
        long long mid = low + (high - low) / 2;
 
        // Find the first index in A where elements are >= mid
        auto it = lower_bound(A.begin(), A.end(), mid);
        int p = distance(A.begin(), it);
 
        // We only care about the suffix from M to N-1
        int effective_p = max(M, min(N, p));
 
        long long count = effective_p - M;
        long long current_sum = pref[effective_p] - pref[M];
 
        // Cost = (number of elements needing boost) * mid - (sum of those elements)
        long long cost = count * mid - current_sum;
 
        if (cost <= K) {
            ans = mid;
            low = mid + 1;  // Try for a higher median
        } else {
            high = mid - 1; // Too expensive, lower our target
        }
    }
 
    cout << ans;
}
