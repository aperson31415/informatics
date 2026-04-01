#include <bits/stdc++.h>
using namespace std;
 
int main() noexcept {
    int N;
    cin >> N;
    cout << N / (1 << __builtin_ctz(N)) << " " << __builtin_ctz(N);
}