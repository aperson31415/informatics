#include <bits/stdc++.h>
using namespace std;
 
signed main() noexcept {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    static int K; cin >> K;
    static string inst; cin >> inst;
 
    vector<pair<int, int>> instructions(K); // DeltaX, DeltaY
 
    for(static int i = 0; i < K; i++) {
        if(inst[i] == 'N') instructions[i] = {1, 0};
        else if(inst[i] == 'E') instructions[i] = {0, 1};
        else if(inst[i] == 'S') instructions[i] = {-1, 0};
        else if(inst[i] == 'W') instructions[i] = {0, -1};
    }
 
    pair<int, int> position;
 
    for(const auto &pair : instructions) {
        position.first += pair.first;
        position.second += pair.second;
    }
 
    cout << abs(position.first) + abs(position.second);
}
