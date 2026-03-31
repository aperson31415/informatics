#include <bits/stdc++.h>
using namespace std;
 
int main() {
    freopen("pairin.txt", "r", stdin);
    freopen("pairout.txt", "w", stdout);
    
    int N, x; cin >> N;
    vector<pair<int, int>> positions(N + 1, {-1, -1});
    for(int i = 0; i < 2*N; i++) {
        cin >> x;
        if(positions[x].first == -1) {positions[x].first = i;}
        else {positions[x].second = i;}
    }
    int max_distance = 0;
    for(int i = 0; i < N; i++) {
        max_distance = max(max_distance, positions[i].second - positions[i].first);
    }
 
    cout << max_distance;
}
