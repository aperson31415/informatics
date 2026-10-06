#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> a, b;

// Returns the number of pairs with sum >= val
int count_ge(int val) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        int target = val - a[i];
        auto it = lower_bound(b.begin(), b.end(), target);
        total += (b.end() - it);
        
        if (total > k) {
            return k + 1;
        }
    }
    return total;
}

int main() {
    cin >> n >> k;
    a.resize(n); 
    b.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    reverse(b.begin(), b.end());

    int lo = 0, hi = a[0] + b.back() + 1;
    int ans = 0;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (count_ge(mid) >= k) {
            ans = mid;
            lo = mid + 1; 
        } else {
            hi = mid - 1;
        }
    }

    cout << ans;
}
