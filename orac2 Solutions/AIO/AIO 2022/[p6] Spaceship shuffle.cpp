#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    int n; cin >> n;
    vector<int> a(n), b(n), diff(n), s(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    for(int i = 0; i < n; i++) diff[i] = b[i] - a[i];

    s[0] = diff[0];
    for(int i = 1; i < n; i++) s[i] = s[i-1] + diff[i];

    vector<int> sorted_s = s;
    sort(sorted_s.begin(), sorted_s.end());

    vector<int> pref_sorted(n);
    pref_sorted[0] = sorted_s[0];
    for(int i = 1; i < n; i++) pref_sorted[i] = pref_sorted[i-1] + sorted_s[i];

    int min_cost = LLONG_MAX;

    for(int k = 0; k < n; k++) {
        int x = s[k];
        auto it = lower_bound(sorted_s.begin(), sorted_s.end(), x);
        int c = distance(sorted_s.begin(), it); // count elements < x

        // Sum for elements <= x: x * c - sum of elements <= x
        int sum_left = (c > 0) ? (x * c - pref_sorted[c - 1]) : 0;

        // Sum for elements > x: sum of elements > x - x * (n - c)
        int sum_right = (pref_sorted[n - 1] - (c > 0 ? pref_sorted[c - 1] : 0)) - x * (n - c);

        int current_cost = sum_left + sum_right;
        min_cost = min(min_cost, current_cost);
    }

    cout << min_cost << "\n";
}
