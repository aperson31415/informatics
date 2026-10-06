#include <bits/stdc++.h>
using namespace std;

struct Budgie {
    int a, b;
};

bool compareBudgies(const Budgie& x, const Budgie& y) {
    if (x.b != y.b) {
        return x.b < y.b;
    }
    return x.a < y.a;
}

int main() {
    freopen("shotin.txt", "r", stdin);
    freopen("shotout.txt", "w", stdout);

    int n; cin >> n;

    vector<Budgie> budgies(n);
    for (int i = 0; i < n; i++) {
        cin >> budgies[i].a >> budgies[i].b;
    }

    // Sort intervals by end time
    sort(budgies.begin(), budgies.end(), compareBudgies);

    int shots = 0;
    int last_shot = -1; // Tracks the time of the most recent photo

    for (int i = 0; i < n; i++) {
        // If the current budgie starts after our last shot, we need a new photo
        if (budgies[i].a > last_shot) {
            shots++;
            last_shot = budgies[i].b; // Place the shot at the end of this budgie
        }
    }

    cout << shots;
}
