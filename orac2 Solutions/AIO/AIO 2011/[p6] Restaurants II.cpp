#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int N, A, B;
    cin >> N >> A >> B;
    vector<pair<int,int>> d(N);
    for (auto &[s, t] : d) cin >> s >> t;

    sort(d.begin(), d.end(), [](auto &x, auto &y) {
        return x.first - x.second > y.first - y.second;
    });

    vector<ll> pref(N + 1, 0), suf(N + 1, 0);
    priority_queue<int, vector<int>, greater<int>> pq;
    ll sum = 0;

    for (int i = 0; i < N; i++) {
        int s = d[i].first;

        if (s > 0) {
            pq.push(s);
            sum += s;

            if ((int)pq.size() > A) {
                sum -= pq.top();
                pq.pop();
            }
        }

        pref[i + 1] = sum;
    }

    priority_queue<int, vector<int>, greater<int>> pq2;
    sum = 0;

    for (int i = N - 1; i >= 0; i--) {
        int t = d[i].second;

        if (t > 0) {
            pq2.push(t);
            sum += t;

            if ((int)pq2.size() > B) {
                sum -= pq2.top();
                pq2.pop();
            }
        }

        suf[i] = sum;
    }

    ll ans = 0;

    // Split between i-1 and i.
    for (int i = 0; i <= N; i++) {
        ans = max(ans, pref[i] + suf[i]);
    }

    cout << ans;
}

