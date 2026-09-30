#include <bits/stdc++.h>
using namespace std;
 
int steps(int N) noexcept {
    int STEP = 0;
    while (true) {
        if(N == 1) return STEP;
 
        ++STEP;
        if(N%2 == 0) N = N/2;
        else N = N*3 + 1;
    }
}
 
int main() noexcept {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    static int N;
    cin >> N;
 
    vector<int> D(N);
 
    for(int i = 0; i < N; i++) cin >> D[i];
 
    int satisfied = 0, current_max = 0, current_eaten = 0;
 
    for(int dish: D) {
        current_eaten += dish;
        if(current_eaten >= current_max) {
            current_max = current_eaten;
            current_eaten = 0;
            satisfied++;
        }
    }
 
    cout << satisfied;
}
