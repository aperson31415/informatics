#include <bits/stdc++.h>
using namespace std;
#define fio(in,out) freopen(in,"r",stdin); freopen(out,"w",stdout)
#define int long long

signed main() {
    fio("divain.txt", "divaout.txt"); 
    int n, t, k; cin >> n >> t >> k;

    int* last_change = new int[n + 1]();

    vector<int> event_days;
    vector<int> event_double_delta;

    // Group events by day
    for(int i = 0; i < k; i++) {
        int d, m, r;
        cin >> d >> m >> r;
        m--;
        if (event_days.empty() || event_days.back() != d) {
            event_days.push_back(d);
            event_double_delta.push_back(0);
        }
        int delta_val = r - last_change[m];
        event_double_delta.back() += delta_val;
        last_change[m] = r;
    }

    delete[] last_change;

    int max_val = 0;
    int best_day = 0;

    auto consider = [&](int val, int day) {
        if (day < 0 || day > t) return;
        if (val > max_val) {
            max_val = val;
            best_day = day;
        } else if (val == max_val) {
            if (day > best_day) {
                best_day = day; // Tie-breaking: choose the last day
            }
        }
    };

    consider(0, 0); // Day 0 check

    int curr_day = 0;
    int curr_f = 0;
    int curr_delta = 0;

    for (size_t i = 0; i < event_days.size(); i++) {
        int d = event_days[i];
        int dd = event_double_delta[i];

        if (d - 1 > curr_day) {
            consider(curr_f + curr_delta * (d - 1 - curr_day), d - 1);
        }

        curr_f = curr_f + curr_delta * (d - curr_day) + dd;
        curr_delta += dd;
        curr_day = d;

        consider(curr_f, curr_day);
    }

    if (curr_day < t) {
        consider(curr_f + curr_delta * (t - 1 - curr_day), t - 1);
        consider(curr_f + curr_delta * (t - curr_day), t);
    }

    cout << best_day << ' ' << max_val;
}
