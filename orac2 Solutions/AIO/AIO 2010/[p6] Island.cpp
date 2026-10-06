#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Event {
    ll x, d;

    bool operator<(const Event& other) const {
        return x < other.x;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll L;
    cin >> N >> L;

    if (L == 0) {
        cout << 0 << '\n';
        return 0;
    }

    ll M = 4 * L;
    ll H = 2 * L;

    vector<Event> events;
    events.reserve(2 * N);

    ll value = 0;
    ll slope = 0;

    for (int i = 0; i < N; ++i) {
        ll h, p;
        cin >> h >> p;
        --h;

        value += p * min(h, M - h);

        if (h == 0 || h > H)
            slope += p;
        else
            slope -= p;

        events.push_back({h, 2 * p});
        events.push_back({(h + H) % M, -2 * p});
    }

    sort(events.begin(), events.end());

    ll ans = value;
    ll prev = 0;
    size_t i = 0;

    while (i < events.size() && events[i].x == 0)
        ++i;

    while (i < events.size()) {
        ll x = events[i].x;

        value += slope * (x - prev);
        ans = max(ans, value);

        while (i < events.size() && events[i].x == x) {
            slope += events[i].d;
            ++i;
        }

        prev = x;
    }

    cout << ans << '\n';
    return 0;
}

