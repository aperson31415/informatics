#include <bits/stdc++.h>
using namespace std;
 
int main() {
    freopen("queuesin.txt", "r", stdin);
    freopen("queuesout.txt", "w", stdout);
 
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    deque<int> q;
    int x;
 
    // Read until EOF
    while (cin >> x) {
        if (x >= 0) {
            // enqueue
            q.push_back(x);
        } else if(x == -1) {
            // dequeue
            if (!q.empty()) {
                q.pop_front();
            } else {
                cout << "queue is empty!\n";
                continue;
            }
        } else {
            return 0;
        }
 
        // print queue
        if (q.empty()) {
            cout << "queue is empty!\n";
        } else {
            for (int v : q) cout << v << " ";
            cout << '\n';
        }
    }
 
    return 0;
}
