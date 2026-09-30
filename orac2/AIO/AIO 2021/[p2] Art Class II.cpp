#include <bits/stdc++.h>
using namespace std;
 
int main() noexcept {
    static int N, X, Y;
    cin >> N;
 
    static int maxX = 0, minX = 100001, maxY = 1, minY = 100001;
 
    for(static int i = 0; i < N; i++) {
        cin >> X >> Y;
        maxX = max(maxX, X);
        maxY = max(maxY, Y);
        minX = min(minX, X);
        minY = min(minY, Y);
    }
 
    cout << (maxX - minX)*(maxY - minY);
}
