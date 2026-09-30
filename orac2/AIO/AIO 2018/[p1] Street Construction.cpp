#include <bits/stdc++.h>
using namespace std;
 
inline int ceildiv(int a, int b) noexcept {
    return a / b + (a%b != 0);
}
 
int main() noexcept {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, K;
    cin >> N >> K;
    cout << ceildiv((N-K),(K+1));
}
