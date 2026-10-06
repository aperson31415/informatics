#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;

    int total_delegates = 0;
    priority_queue<int> pq;

    for (int i = 0; i < n; ++i) {
        int d;
        cin >> d;
        total_delegates += d;
        if (d > 0) {
            pq.push(d);
        }
    }

    int m; cin >> m;
    vector<int> restaurants(m);
    for (int i = 0; i < m; ++i) {
        cin >> restaurants[i];
    }

    sort(restaurants.rbegin(), restaurants.rend());
    int total_seated = 0;

    // Greedily fill restaurants
    for (int cap : restaurants) {
        if (pq.empty()) break;

        vector<int> temp;
        int take = min(cap, (int)pq.size());

        for (int i = 0; i < take; ++i) {
            int count = pq.top();
            pq.pop();
            total_seated++;
            count--;
            if (count > 0) {
                temp.push_back(count);
            }
        }

        for (int count : temp) {
            pq.push(count);
        }
    }

    cout << total_delegates - total_seated;
}
