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
 
    int N;
 
    while (true) {
        cin >> N;
        if (N == 0) return 0;
        cout << steps(N) << "\n";
    }
}