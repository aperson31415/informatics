#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int B, N, x;
    cin >> B >> N;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> A;
    for(int i = 1; i <= B; i++) {
        cin >> x;
        A.push({x, i});
    }
 
    // Do main loop
    int curr_lvl = 0;
    while(N > A.size()) {
        int more_lvls = min((N - 1) / (int)A.size(), A.top().first - curr_lvl);
        N -= more_lvls * A.size();
        curr_lvl += more_lvls;
        while(A.top().first == curr_lvl) A.pop();
    }
 
    // Do rest of stuff
    vector<int> non_empty;
    while(!A.empty()) {
        non_empty.push_back(A.top().second);
        A.pop();
    }
 
    sort(non_empty.begin(), non_empty.end());
    cout << non_empty[N - 1];
}
