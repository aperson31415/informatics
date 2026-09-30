#include <bits/stdc++.h>
using namespace std;
 
signed main() noexcept {
    int N, D; 
    cin >> N;
    int current_leader = -1;
    int current_leaders = 0;
    for(int i = 0; i < N; i++) {
        cin >> D;
        if(D > current_leader) {
            current_leaders += 1;
            current_leader = D;
        }
    }
 
    cout << current_leaders;
}
