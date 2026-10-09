#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int N; cin >> N;

    vector<ll> a(N), b(N), c(N), d(N);

    for (int i = 0; i < N; i++) cin >> a[i] >> b[i];
    for (int i = 0; i < N; i++) cin >> c[i] >> d[i];

    // {shift position, change in slope}.
    vector<pair<ll, ll>> events;
    events.reserve(4 * N);

    for (int i = 0; i < N; i++) {
        events.push_back({a[i] - d[i] - 1, +1});
        events.push_back({b[i] - d[i], -1});
        events.push_back({a[i] - c[i], -1});
        events.push_back({b[i] + 1 - c[i], +1});
    }

    sort(events.begin(), events.end());

    ll area = 0;
    ll slope = 0;
    ll ans = 0;
    ll prev = events[0].first;

    int i = 0;
    while (i < (int)events.size()) {
        ll x = events[i].first;

        area += slope * (x - prev);
        ans = max(ans, area);

        while (i < (int)events.size() &&
               events[i].first == x) {
            slope += events[i].second;
            i++;
        }

        prev = x;
    }

    cout << ans;
}
