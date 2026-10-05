#include <bits/stdc++.h>
using namespace std;
 
int n;
 
int seat[13];
bool used[13];
 
bool together[13][13];
bool apart[13][13];
 
bool allowed(int a, int b) {
    if (apart[a][b])
        return false;
 
    return true;
}
 
bool solve(int pos) {
 
    // All seats have been filled
    if (pos == n) {
 
        if (!allowed(seat[n - 1], seat[0]))
            return false;
 
        for (int a = 1; a <= n; a++) {
            for (int b = a + 1; b <= n; b++) {
 
                if (together[a][b]) {
 
                    bool adjacent = false;
 
                    // Find knight a
                    for (int i = 0; i < n; i++) {
 
                        if (seat[i] == a) {
 
                            // Check both neighbours of a
                            if (seat[(i + 1) % n] == b ||
                                seat[(i - 1 + n) % n] == b) {
                                adjacent = true;
                            }
 
                            break;
                        }
                    }
 
                    if (!adjacent)
                        return false;
                }
            }
        }
 
        // We found a valid seating!
        for (int i = 0; i < n; i++) {
            if (i > 0)
                cout << ' ';
 
            cout << seat[i];
        }
 
        cout << '\n';
 
        return true;
    }
 
    // Try every knight that hasn't been seated yet
    for (int x = 2; x <= n; x++) {
 
        if (used[x])
            continue;
 
        if (!allowed(x, seat[pos - 1]))
            continue;
 
        used[x] = true;
        seat[pos] = x;
 
        // Continue building the seating
        if (solve(pos + 1))
            return true;
 
        // Backtrack
        used[x] = false;
    }
 
    return false;
}
 
int main() {
 
    cin >> n;
 
    int a, b;
 
    // Read "must sit together" pairs
    while (cin >> a >> b) {
 
        if (a == 0 && b == 0)
            break;
 
        together[a][b] = true;
        together[b][a] = true;
    }
 
    // Read "must NOT sit together" pairs
    while (cin >> a >> b) {
 
        if (a == 0 && b == 0)
            break;
 
        apart[a][b] = true;
        apart[b][a] = true;
    }
 
    seat[0] = 1;
    used[1] = true;
 
    if (!solve(1))
        cout << "Meeting cancelled.\n";
 
    return 0;
}
