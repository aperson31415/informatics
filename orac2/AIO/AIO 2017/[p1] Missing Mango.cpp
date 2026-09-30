#include <bits/stdc++.h>
using namespace std;
 
int main() noexcept {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    static int ax, bx, ad, bd;
    cin >> ax >> bx >> ad >> bd;
    static int distance;
 
    if(bx + bd == ax - ad or bx + bd == ax + ad) distance = bx + bd;
    else distance = bx - bd;
 
    cout << distance;
    
}
