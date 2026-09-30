#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int N; cin >> N;
    vector<int> heights(N); for(int i = 0; i < N; i++) cin >> heights[i];
 
    // Generate ones bigger than current, to left
    vector<int> big_toleft = {0};
    for(int i = 1; i < N; i++) {
        big_toleft.push_back(max(big_toleft[i - 1], heights[i - 1]));
    }
 
    // Generate ones bigger than current, to right
    vector<int> big_toright(N, 0);
    for(int i = N - 1; i > 0; i--) {
        big_toright[i - 1] = max(big_toright[i], heights[i]);
    }
 
    // Loop through columns
    int H = 0;
 
    for(int i = 0; i < N; i++) {
        int smallmax = min(big_toright[i], big_toleft[i]);
        if(smallmax > heights[i]) {
            H++;
        }
    }
 
    cout << H;
}