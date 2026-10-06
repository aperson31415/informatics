#pragma GCC optimize("Ofast,unroll-loops,inline-functions")
#pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;
 
consteval inline array<int, 100001> cache() noexcept {
    array<int, 100001> arr{};
    for (int i = 1; i < 100001; i++) {
        if(i < 6) { 
            arr[i] = 0;
        } else {
            arr[i] = i - 3;
        }
    }
    return arr;
}
 
constexpr array<int, 100001> stuff = cache();
 
int main() noexcept {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    static int N;
    cin >> N;
 
    if(stuff[N] == 0) {
        cout << "0 0 0";
    } else {
        cout << "1 2 " << stuff[N];
    }
}
